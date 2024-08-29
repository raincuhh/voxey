#pragma once

#include <iostream>
//#include <chrono>

#include "../../include/glad/glad.h"
#include "../../include/GLFW/glfw3.h"

class Time
{
public:
	Time(GLFWwindow* window);
	~Time();

	void timeUpdate();
	double getDeltaTime() const;
	double getFixedDeltaTime() const;

private:
	GLFWwindow* mWindow;
	double deltaTime;
	double previousTime;
	double fixedDeltaTime;
};

