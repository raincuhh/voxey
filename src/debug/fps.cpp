#include "fps.h"

Debug::Fps::Fps() : frames(0), previousSecond(GraphicsManager::getTime())
{
}

void Debug::Fps::fpsUpdate()
{
	double fpsCurrent = GraphicsManager::getTime();
	frames++;

	if (fpsCurrent - previousSecond >= 1.0)
	{
		std::printf("%f ms/frames\n", 1000.0 / double(frames));
		frames = 0;
		previousSecond += 1.0;
	}
}
