#include "time.h"

double Utils::Time::deltaTime;
double Utils::Time::fixedDeltaTime;
double Utils::Time::previousTime;

Utils::Time::Time()
{
	fixedDeltaTime = 1.0 / 60.0;
	previousTime = glfwGetTime();
}

Utils::Time::~Time()
{
}

void Utils::Time::timeUpdate()
{
	double currentTime = glfwGetTime();
	deltaTime = static_cast<double>(currentTime - previousTime);
	previousTime = currentTime;
}

double Utils::Time::getDeltaTime()
{
	return deltaTime;
}

double Utils::Time::getFixedDeltaTime()
{
	return fixedDeltaTime;
}
