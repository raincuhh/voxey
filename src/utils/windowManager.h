#pragma once

#include "../../include/glad/glad.h"
#include "../../include/GLFW/glfw3.h"

class WindowManager
{
public:


	bool createWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
	int gladInit();
	int glfwInit();
	void pollEvents();
	void swapBuffers(GLFWwindow* window);
	bool shouldClose();

	const auto getPrimaryMonitor(GLFWwindow* window);
	const auto getVideoMode(GLFWwindow* window);

	void setWindowPos(GLFWwindow* window, int xPos, int yPos);
	void setCurrentContext(GLFWwindow* window);
	void setFrameBufferCallback(GLFWwindow* window, auto callback);

private:

};
