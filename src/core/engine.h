#pragma once

#include <iostream>
#include <chrono>

#include "../../include/glad/glad.h"
#include "../../include/GLFW/glfw3.h"

#include "../rendering/renderer.h"
#include "../physics/physics.h"
#include "../utils/time.h"

class Engine
{
private:
	GLFWwindow* mWindow;
	Engine* mEngine;
	Renderer* mRenderer;
	Time* mTime;
	Physics* mPhysics;

public:
	Engine(GLFWwindow* window);
	~Engine();
	int run();
	void engineUpdate(double deltaTime);
	void fixedUpdate(double fixedDeltaTime);
};