#include "windowManager.h"

bool WindowManager::createWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{
	return false;
}

int WindowManager::gladInit()
{
	return gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

int WindowManager::glfwInit()
{
	return glfwInit();
}

void WindowManager::pollEvents()
{
	glfwPollEvents();
}
