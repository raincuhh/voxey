#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>
#include <vector>
#include <memory>

#include "../../include/glad/glad.h"
#include "../../include/GLFW/glfw3.h"

#include "../../include/glm/glm.hpp"

#include "../utils/shaderManager.h"
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

	ShaderManager* mShaderManager;
	GLuint mShaderProgram;

	glm::mat4 mView;
	glm::mat4 mProj;

	std::vector<unsigned int> compiledShaderList;
	std::vector<Block> blockList;

	unsigned int mVAO;
	unsigned int mEBO;

	void setupShaderProgram();
};
