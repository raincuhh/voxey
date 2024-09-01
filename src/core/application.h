#pragma once

#include <iostream>

#include "../../include/glad/glad.h"
#include "../../include/GLFW/glfw3.h"

#include "logger.h"
#include "engine.h"
#include "../input/inputManager.h"
#include "../utils/windowManager.h"


namespace EntryPoint
{
	class Application
	{
	public:
		~Application();
		int run();
		int init();

		GLFWwindow* getWindow() const;

	private:
		GLFWwindow* mWindow;

		Logger* mLogger;
		Engine::Engine* mEngine;
		InputManager* mInputManager;

		int createWindow();
		static void frameBufferCallback(GLFWwindow* window, int width, int height);
		void setupDefaultKeybinds();
		void setupDebugKeybinds();

		static void changeGLPolygonMode();
	};
}

/*
class Application
{
public:
	~Application();
	int run();
	int init();

	GLFWwindow* getWindow() const;

private:
	GLFWwindow* mWindow;

	Logger* mLogger;
	Engine* mEngine;
	InputManager* mInputManager;

	int createWindow();
	static void frameBufferCallback(GLFWwindow* window, int width, int height);
	void setupDefaultKeybinds();
	void setupDebugKeybinds();

	static void changeGLPolygonMode();
};

*/