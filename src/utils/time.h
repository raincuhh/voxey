#pragma once

#include <iostream>

#include "graphicsManager.h"

namespace voxey::utils
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



