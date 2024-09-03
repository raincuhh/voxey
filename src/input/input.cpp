#include "input.h"

std::unordered_map<Action, std::set<Key>> voxey::input::Input::actionMap;
std::set<Key> voxey::input::Input::pressedKeys;
std::set<Key> voxey::input::Input::previousPressedKeys;

float voxey::input::Input::lastX = 640.0f;
float voxey::input::Input::lastY = 360.0f;

bool voxey::input::Input::mouseMoved = false;
bool voxey::input::Input::firstMouse = true;

float voxey::input::Input::sensitivity = 0.1f;

float voxey::input::Input::yaw = -90.0f;
float voxey::input::Input::pitch = 90.0f;

glm::vec3 voxey::input::Input::direction = glm::vec3(0.0f, 0.0f, 0.0f);


void voxey::input::Input::init(GLFWwindow* window, Input* instance)
{
	glfwSetWindowUserPointer(window, instance);

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_FALSE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetKeyCallback(window, glfwKeyCallback);
	glfwSetCursorPosCallback(window, glfwMouseCallback);
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

bool voxey::input::Input::isActionJustReleased(const Action& action)
{
	auto it = actionMap.find(action);
	if (it != actionMap.end())
	{
		for (Key key : it->second)
		{
			if (previousPressedKeys.find(key) != previousPressedKeys.end())
			{
				return true;
			}
		}
	}
	return false;
}

glm::vec3 voxey::input::Input::getDirection()
{
	return direction;
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

void voxey::input::Input::glfwMouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	/*
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	float xOffset = xPos - lastX;
	float yOffset = lastY - yPos;

	lastX = xPos;
	lastY = yPos;

	xOffset *= sensitivity;
	yOffset *= sensitivity;

	yaw += xOffset;
	pitch += yOffset;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}

	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	std::cout << "Yaw: " << yaw << " Pitch: " << pitch << std::endl;
	std::cout << "direction: (" << xPos << ", " << yPos << ")" << std::endl;
	*/
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
