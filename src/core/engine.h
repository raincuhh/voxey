#pragma once

#include <iostream>
#include <chrono>

#include "../utils/graphicsManager.h"
#include "../rendering/renderer.h"
#include "../physics/physics.h"
#include "../utils/time.h"
#include "../debug/fps.h"

namespace Engine 
{
	class Engine
	{
	private:
		GLFWwindow* mWindow;
		Engine* mEngine;
		Rendering::Renderer* mRenderer;
		Utils::Time* mTime;
		Physics* mPhysics;

	public:
		Engine(GLFWwindow* window);
		~Engine();
		int run();
		void engineUpdate(double timeAccu, const double fixedDeltaTime);
	};
}