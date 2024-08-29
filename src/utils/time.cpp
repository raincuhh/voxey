#include "time.h"

Time::Time(GLFWwindow* window) : mWindow(window), deltaTime(0.0), previousTime(0.0), fixedDeltaTime(0.0)
{
	fixedDeltaTime = 1.0 / 60.0;
	double previousTime = glfwGetTime();
}

Time::~Time()
{
}

void Time::timeUpdate()
{
	double currentTime = glfwGetTime();
	deltaTime = currentTime - previousTime;
	previousTime = currentTime;
}

double Time::getDeltaTime() const
{
	return deltaTime;
}

double Time::getFixedDeltaTime() const
{
	return fixedDeltaTime;
}
