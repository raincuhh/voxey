#include "fps.h"

voxey::debug::Fps::Fps() : 
	frames(0), 
	previousSecond(glfwGetTime())
{
}

void voxey::debug::Fps::fpsUpdate()
{
	double fpsCurrent = glfwGetTime();
	frames++;

	if (fpsCurrent - previousSecond >= 1.0)
	{
		std::cout << frames << std::endl;
		frames = 0;
		previousSecond += 1.0;
	}
}
