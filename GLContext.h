#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

	unsigned int makeShader(const char* shaderSource, unsigned int shaderType);

	const char* vertexShaderSource { nullptr };
	const char* fragmentShaderSource{ nullptr };

	unsigned int mShaderProgram;
	unsigned int mVBO { 0 };
	unsigned int mVAO { 0 };

	GLFWwindow* mWindow = nullptr;
};

