#pragma once

#include <iostream>
#include <chrono>

#include "../../include/glad/glad.h"
#include "../../include/GLFW/glfw3.h"

class Time
{
public:

	Time(GLFWwindow* window);
	~Time();
	void update();
	double getDeltaTime() const;
	std::chrono::time_point<std::chrono::high_resolution_clock> getCurrentTime();
	double getFixedDeltaTime() const;

private:
	GLFWwindow* mWindow;

	std::chrono::duration<double> deltaTime;
	std::chrono::time_point<std::chrono::high_resolution_clock> previousTime;
	double fixedDeltaTime;
};

