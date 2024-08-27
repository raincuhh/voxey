#include "time.h"

Time::Time(GLFWwindow* window) : mWindow(window), deltaTime(0.0)
{
	fixedDeltaTime = 1.0 / 60.0;
	auto previousTime = std::chrono::time_point<std::chrono::high_resolution_clock>();

}

Time::~Time()
{
}

void Time::update()
{
	auto currentTime = std::chrono::time_point<std::chrono::high_resolution_clock>();


	deltaTime = currentTime - previousTime;
	previousTime = currentTime;
}

double Time::getDeltaTime() const
{
	return deltaTime.count();
}

std::chrono::time_point<std::chrono::high_resolution_clock> Time::getCurrentTime()
{
	return std::chrono::time_point<std::chrono::high_resolution_clock>();
}

double Time::getFixedDeltaTime() const
{
	return fixedDeltaTime;
}
