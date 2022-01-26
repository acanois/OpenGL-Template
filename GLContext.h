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

	GLFWwindow* mWindow = nullptr;
};

