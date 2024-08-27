#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>
#include <vector>

#include "../../include/glad/glad.h"
#include "../../include/GLFW/glfw3.h"

#include "../../include/glm/glm.hpp"

#include "../utils/fileManager.h"
#include "../voxel/block.h"

class Renderer
{
public:
	Renderer(GLFWwindow* window);
	~Renderer();
	void init();
	void renderUpdate(double dt) const;

private:
	GLFWwindow* mWindow;
	unsigned int mShaderProgram;

	std::vector<unsigned int> compiledShaderList;
	std::vector<Block> blockList;
	Block *block1;

	unsigned int mVAO;
	unsigned int mEBO;

	unsigned int setupShaderProgram();
	int debugShader(unsigned int shader) const;
	unsigned int createShader(GLenum type, const GLchar* shader);
	unsigned int linkShaderProgram(unsigned int program, const std::vector<unsigned int> &shaders);
};
