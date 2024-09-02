#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <cctype>
#include <string>

#include "../../include/glad/glad.h"
#include "../../include/GLFW/glfw3.h"

namespace voxey::core
{
	class Logger
	{
	public:
		Logger();
		~Logger();

		static void run();
		static void glfwErrorCallback(int err, const char* desc);
		static void dPrint(const char* name, const char* desc, const std::vector<std::string>& args);

	private:

	};
}

