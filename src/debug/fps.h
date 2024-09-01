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
		void fpsUpdate();

	private:
		unsigned int frames;
		double previousSecond;
	};
}