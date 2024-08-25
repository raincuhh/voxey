#include "inputManager.h"

InputManager::InputManager(GLFWwindow* window) : mWindow(window)
{
	glfwSetKeyCallback(window, windowKeyCallback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
}

void InputManager::windowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	InputManager* inputManager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
	if (inputManager)
	{
		inputManager->handleKeyEvent(key, scancode, action, mods);
	}
	else
	{
		std::cout << "key event: " << key << ", action=" << action << std::endl;
	}
}

void InputManager::handleKeyEvent(int key, int scancode, int action, int mods)
{
	(void)scancode;

	if (action == GLFW_PRESS)
	{
		std::cout << "key pressed: " << key << std::endl;
	}
	else if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		// glfwSetWindowShouldClose(mWindow, GLFW_TRUE);
	}
	else if (action == GLFW_RELEASE)
	{
	}
	else if (mods && GLFW_MOD_SHIFT)
	{
		std::cout << "type shi" << std::endl;
	}
}
