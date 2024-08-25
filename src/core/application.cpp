#include "application.h"

Application::~Application()
{
}

int Application::run()
{
	std::cout << "running application" << std::endl;
	return 0;
}

int Application::init()
{
	return 0;
}

GLFWwindow* Application::getWindow() const
{
	return nullptr;
}

int Application::createWindow()
{
	return 0;
}

void Application::frameBufferCallback(GLFWwindow* window, unsigned int width, unsigned int height)
{
}
