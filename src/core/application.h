#pragma once

#include <iostream>
#include <memory>

#include "logger.h"
#include "engine.h"
#include "../input/input.h"

#include "../../include/glad/glad.h"
#include "../../include/GLFW/glfw3.h"



namespace voxey::core
{
	class Application
	{
	public:
		Application(int argc, char** argv[]);
		~Application();

		int run();

		GLFWwindow* getWindow();

	private:
		GLFWwindow* mWindow;

		std::unique_ptr<voxey::core::Logger> mLogger;
		std::unique_ptr<voxey::core::Engine> mEngine;
		std::unique_ptr<voxey::input::Input> mInputManager;

		int createWindow();
		static void frameBufferCallback(GLFWwindow* window, int width, int height);
		void setupDefaultKeybinds();
		void setupDebugKeybinds();
		static void changeGLPolygonMode();
	};
}

