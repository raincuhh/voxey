#include "time.h"

double Time::deltaTime;
double Time::fixedDeltaTime;
double Time::previousTime;

Time::Time()
{
	fixedDeltaTime = 1.0 / 60.0;
	previousTime = glfwGetTime();
}

Time::~Time()
{
}

void Time::timeUpdate()
{
	double currentTime = glfwGetTime();
	deltaTime = static_cast<double>(currentTime - previousTime);
	previousTime = currentTime;
}

double Time::getDeltaTime() 
{
	return deltaTime;
}

double Time::getFixedDeltaTime()
{
	return fixedDeltaTime;
}
