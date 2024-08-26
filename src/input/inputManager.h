#pragma once
#include <iostream>

#include "../../include/glad/glad.h"
#include "../../include/GLFW/glfw3.h"

class InputManager
{
public:
	InputManager(GLFWwindow* window);

private:
	GLFWwindow* mWindow;

	static void windowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void handleKeyEvent(int key, int scancode, int action, int mods);
};
