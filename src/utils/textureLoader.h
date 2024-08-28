#pragma once

#include <iostream>
#include <string>

#include "../../include/glad/glad.h"
#include "../../include/GLFW/glfw3.h"

#include "../../include/stb-master/stb_image.h"


class TextureLoader
{
public:
	static int LoadTexture(const std::string& filePath, unsigned int& texture);
};