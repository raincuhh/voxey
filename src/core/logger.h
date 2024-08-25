#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <cctype>
#include <string>

#include "../../include/glad/glad.h"
#include "../../include/GLFW/glfw3.h"

class Logger
{
public:
	Logger();
	~Logger();

	static void run();
	static void glfwErrorCallback(int err, const char* desc);
	void dPrint(const char* name, char* desc, const std::vector<std::string>& args);

private:

};