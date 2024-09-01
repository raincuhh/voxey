#pragma once

#include <iostream>
#include <memory>
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
	public:
		Engine(GLFWwindow* window);
		~Engine();
		int run();
		void engineUpdate(double timeAccu, const double fixedDeltaTime);

	private:
		GLFWwindow* mWindow;

		std::unique_ptr<Utils::Time> mTime;
		std::unique_ptr<Rendering::Renderer> mRenderingEngine;
		std::unique_ptr<Physics> mPhysicsEngine;
	};
}