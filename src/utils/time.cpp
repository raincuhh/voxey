#include "time.h"

double voxey::utils::Time::deltaTime;
double voxey::utils::Time::fixedDeltaTime;
double voxey::utils::Time::previousTime;

voxey::utils::Time::Time()
{
	fixedDeltaTime = 1.0 / 60.0;
	previousTime = glfwGetTime();
}

voxey::utils::Time::~Time()
{
}

void voxey::utils::Time::timeUpdate()
{
	double currentTime = glfwGetTime();
	deltaTime = static_cast<double>(currentTime - previousTime);
	previousTime = currentTime;
}

double voxey::utils::Time::getDeltaTime()
{
	return deltaTime;
}

double voxey::utils::Time::getFixedDeltaTime()
{
	return fixedDeltaTime;
}
