#pragma once

#include <iostream>
#include <memory>
#include <chrono>

#include "../../include/glad/glad.h"
#include "../../include/GLFW/glfw3.h"

#include "../rendering/renderingEngine.h"
#include "../physics/physicsEngine.h"

#include "../utils/time.h"
#include "../input/input.h"
#include "../debug/fps.h"

namespace voxey::core
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

		std::unique_ptr <voxey::debug::Fps> mFps;
		std::unique_ptr<voxey::utils::Time> mTime;
		std::unique_ptr<voxey::rendering::RenderingEngine> mRenderingEngine;
		std::unique_ptr<voxey::physics::PhysicsEngine> mPhysicsEngine;

		void changePolygonMode();
	};
}