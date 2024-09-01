#pragma once

#include <iostream>
#include <string>

#include "graphicsManager.h"

#include "../../include/stb-master/stb_image.h"

namespace Utils
{
	class TextureLoader
	{
	public:
		static int LoadTexture(const std::string& filePath, GLuint& texture);
	};
}

