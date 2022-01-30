#pragma once

#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ShaderManager.h"

class GLContext
{
public:
	GLContext();
	~GLContext();

	GLContext(const GLContext& other);
	GLContext(GLContext&& other) noexcept;
	GLContext& operator=(const GLContext& other) noexcept {};
	GLContext& operator=(GLContext&& other) noexcept {};

	void run();

private:
	bool initGlad();
	bool initGL();
	bool makeNewWindow();

	void processInput(GLFWwindow* window);

	void makeTriangle();
	void makeQuad();
	void makeTexturedQuad();

	void loadTexture(const std::string& path);

	// Metrics
	void showMaxVertexAttribs() {
		int nrAttributes;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
		std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
	}

	unsigned int mShaderProgram;
	unsigned int mVBO { 0 };
	unsigned int mVAO { 0 };
	unsigned int mEBO { 0 };

	unsigned int mTexture { 0 };

	GLFWwindow* mWindow { nullptr };

	std::unique_ptr<ShaderManager> mShaderManager { nullptr };
};

