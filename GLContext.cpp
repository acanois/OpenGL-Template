#include "GLContext.h"

GLContext::GLContext() {
	if (initGL()) {
		std::cout << "GL initialized" << std::endl;
		if (makeNewWindow()) {
			std::cout << "Window created" << std::endl;
			if (initGlad()) {
				std::cout << "GLAD initialized" << std::endl;
			}
		}
	}
}

GLContext::~GLContext() {
	std::cout << "Destroying objects" << std::endl;
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
	mWindow = glfwCreateWindow(1280, 720, "GL Context", nullptr, nullptr);
	if (mWindow == nullptr) {
		std::cout << "Failed to initialize window: " << glfwGetError << std::endl;
		glfwTerminate();
		return false;
	} else {
		std::cout << "Window created successfully." << std::endl;
		glfwMakeContextCurrent(mWindow);
		return true;
	}
}

void GLContext::processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void GLContext::run() {
	while (!glfwWindowShouldClose(mWindow)) {
		processInput(mWindow);

		glfwSwapBuffers(mWindow);
		glfwPollEvents();
	}
}