#include "GLContext.h"

// Move this
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

GLContext::GLContext() {
	if (initGL()) {
		std::cout << "GL initialized" << std::endl;
		if (makeNewWindow()) {
			std::cout << "Window created" << std::endl;
			if (initGlad()) {
				std::cout << "GLAD initialized" << std::endl;
				showMaxVertexAttribs();
			}
		}
	}

	// get shader paths
	auto currentPath = std::filesystem::current_path();
	std::cout << "current_path" << currentPath << std::endl;
	auto vertPath = currentPath / "default_vert.glsl";
	auto fragPath = currentPath / "default_frag.glsl";
	mShaderManager = std::make_unique<ShaderManager>(
		vertPath.string().c_str(),
		fragPath.string().c_str()
	);

	// GENERATE THE TRIANGLE ARRAYS
	//makeTriangle();
	makeQuad();
}

GLContext::~GLContext() {
	std::cout << "Destroying objects" << std::endl;

	glDeleteVertexArrays(1, &mVAO);
	glDeleteBuffers(1, &mVBO);
	glDeleteProgram(mShaderProgram);

	glfwTerminate();
}

GLContext::GLContext(const GLContext& other) {

}

GLContext::GLContext(GLContext&& other) noexcept {

}

bool GLContext::initGlad() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	} else {
		return true;
	}
}

bool GLContext::initGL() {
	if (glfwInit()) {
		std::cout << "GLFW Initialized" << std::endl;
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if defined(__APPLE__)
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE)
#endif
		return true;
	} else {
		std::cout << "GLFW Failed to initialize" << std::endl;
		return false;
	}
}

bool GLContext::makeNewWindow() {
	mWindow = glfwCreateWindow(1024, 768, "GL Context", nullptr, nullptr);
	if (mWindow == nullptr) {
		std::cout << "Failed to initialize window: " << glfwGetError << std::endl;
		glfwTerminate();
		return false;
	} else {
		std::cout << "Window created successfully." << std::endl;
		glfwMakeContextCurrent(mWindow);
		glfwSetFramebufferSizeCallback(mWindow, framebuffer_size_callback);
		return true;
	}
}


void GLContext::processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void GLContext::makeTriangle() {
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};
	// VBO stores vertices and sends them to GPU all at once;
	glGenVertexArrays(1, &mVAO);
	glGenBuffers(1, &mVBO);  // Generates a buffer ID
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(mVAO);

	glBindBuffer(GL_ARRAY_BUFFER, mVBO);  // GL_ARRAY_BUFFER is the buffer type for the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void GLContext::makeQuad() {
	/** ELEMENT BUFFER OBJECTS
	* An EBO is a buffer, just like a vertex buffer object, that stores indices that 
	* OpenGL uses to decide what vertices to draw. This is to prevent redundant vertex
	* definitions.
	*/

	float vertices[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	// Bind the array buffer
	glGenVertexArrays(1, &mVAO);
	glGenBuffers(1, &mVBO);
	glGenBuffers(1, &mEBO);

	glBindVertexArray(mVAO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Bind the element buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// Set the vertex attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void GLContext::run() {
	while (!glfwWindowShouldClose(mWindow)) {
		// Process key commands
		processInput(mWindow);

		// Background Color
		glClearColor(0.2, 0.1, 0.3, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		// Update
		auto timeValue = glfwGetTime();
		auto blueValue = (sin(timeValue) * 0.5) + 0.5f;
		auto shaderProgramId = mShaderManager->getShaderProgram();
		auto vertexColorLocation = glGetUniformLocation(shaderProgramId, "uColor");

		// Draw
		mShaderManager->use();
		glUniform4f(vertexColorLocation, 0.0f, 0.0f, blueValue, 1.0f);
		glBindVertexArray(mVAO); 
		
		// For mutliple triangles
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// Draw
		glfwSwapBuffers(mWindow);
		glfwPollEvents();
	}
}