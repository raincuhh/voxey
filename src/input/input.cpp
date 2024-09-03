#include "input.h"

std::unordered_map<Action, std::set<Key>> voxey::input::Input::actionMap;
std::set<Key> voxey::input::Input::pressedKeys;
std::set<Key> voxey::input::Input::previousPressedKeys;

void voxey::input::Input::init(GLFWwindow* window, Input* instance)
{
	glfwSetWindowUserPointer(window, instance);
	glfwSetKeyCallback(window, glfwKeyCallback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_FALSE);
}

void voxey::input::Input::inputUpdate()
{
	previousPressedKeys = pressedKeys;
}

void voxey::input::Input::registerAction(const Action& action, Key key)
{
	actionMap[action].insert(key);
}

void voxey::input::Input::unRegisterAction(const Action& action)
{
	actionMap.erase(action);
}

bool voxey::input::Input::isActionPressed(const Action& action)
{
	auto it = actionMap.find(action);
	if (it != actionMap.end())
	{
		for (Key key : it->second)
		{
			if (pressedKeys.find(key) != pressedKeys.end())
			{
				return true;
			}
		}
	}
	return false;
}

bool voxey::input::Input::isActionJustPressed(const Action& action)
{
	auto it = actionMap.find(action);
	if (it != actionMap.end())
	{
		for (Key key : it->second)
		{
			if (pressedKeys.find(key) != pressedKeys.end() && previousPressedKeys.find(key) != previousPressedKeys.end())
			{
				return true;
			}
		}
	}
	return false;
}


void voxey::input::Input::glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		pressedKeys.insert(key);
	}
	else if (action == GLFW_RELEASE)
	{
		pressedKeys.erase(key);
	}
}

void voxey::input::Input::setKeyPressed(Key key, bool pressed)
{
	if (pressed)
	{
		pressedKeys.insert(key);
	}
	else
	{
		pressedKeys.erase(key);
	}
}
