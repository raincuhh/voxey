#pragma once 

#include <iostream>

#include "../../include/glad/glad.h"
#include "../../include/GLFW/glfw3.h"

namespace Debug
{
	class Fps
	{
	public:
		Fps();
		void updateFps();

	private:
		unsigned frames;
		double previousSecond;
	};
}