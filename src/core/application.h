#pragma once

#include <iostream>
#include <memory>

#include "logger.h"
#include "engine.h"
#include "../input/inputManager.h"
#include "../utils/graphicsManager.h"


class Application
{
public:
	Application(int argc, char** argv[]);
	~Application();

	int run();
	int init();

	GLFWwindow* getWindow();
	void escapeApplication();

private:
	GLFWwindow* mWindow;

	std::unique_ptr<Logger> mLogger;
	std::unique_ptr<Engine::Engine> mEngine;
	std::unique_ptr<InputManager> mInputManager;

	int createWindow();
	static void frameBufferCallback(GLFWwindow* window, int width, int height);
	void setupDefaultKeybinds();
	void setupDebugKeybinds();
	static void changeGLPolygonMode();
};