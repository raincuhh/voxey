#pragma once

#include <iostream>
//#include <chrono>

#include "graphicsManager.h"

namespace Utils
{
	class Time
	{
	public:
		Time();
		~Time();

		void timeUpdate();
		static double getDeltaTime();
		static double getFixedDeltaTime();

	private:
		static double deltaTime;
		static double previousTime;
		static double fixedDeltaTime;
	};
}



