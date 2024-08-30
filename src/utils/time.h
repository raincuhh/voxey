#pragma once

#include <iostream>
//#include <chrono>

#include "../../include/glad/glad.h"
#include "../../include/GLFW/glfw3.h"

class Time
{
public:
	Time();
	~Time();

	void timeUpdate();
	static double getDeltaTime();
	static double getFixedDeltaTime();

private:
	static double deltaTime;
	static double previousTime;
	static double fixedDeltaTime;
};

