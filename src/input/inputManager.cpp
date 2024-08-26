#include "inputManager.h"

InputManager::InputManager(GLFWwindow* window) : mWindow(window)
{
	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, windowKeyCallback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_FALSE);
}

void InputManager::windowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	InputManager* instance = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
	if (instance)
	{
		instance->handleKeyEvent(key, scancode, action, mods);
	}
	else
	{
		std::cout << "key event: " << key << ", action=" << action << std::endl;
	}
}

void InputManager::handleKeyEvent(int key, int scancode, int action, int mods)
{
	(void)scancode;

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(mWindow, GLFW_TRUE);
	}
	else if (action == GLFW_RELEASE)
	{
	}
	else if (mods && GLFW_MOD_SHIFT)
	{
		std::cout << "shift" << std::endl;
	}
	else if (key == GLFW_KEY_T && action == GLFW_PRESS)
	{
		if (!wireFrameMode)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			wireFrameMode = true;
			std::cout << "glPolygonMode: GL_LINE" << std::endl;
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			wireFrameMode = false;
			std::cout << "glPolygonMode: GL_FILL" << std::endl;
		}
	}
}
