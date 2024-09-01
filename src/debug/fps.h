#pragma once 

#include <iostream>
#include "../utils/graphicsManager.h"


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