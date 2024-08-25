#pragma once

#include <iostream>

#include "../../include/glad/glad.h"
#include "../../include/GLFW/glfw3.h"


class Application
{
public:
	~Application();
	int run();
	int init();

	GLFWwindow* getWindow() const;

private:
	GLFWwindow* mWindow;

	int createWindow();
	static void frameBufferCallback(GLFWwindow* window, unsigned int width, unsigned int height);

};
