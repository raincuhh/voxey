#include "fps.h"

Debug::Fps::Fps() : frames(0), previousSecond(glfwGetTime())
{
}

void Debug::Fps::updateFps()
{
	double fpsCurrent = glfwGetTime();
	frames++;
	if (fpsCurrent - previousSecond >= 1.0)
	{
		std::printf("");
		frames = 0;
		previousSecond += 1.0;
	}
}
