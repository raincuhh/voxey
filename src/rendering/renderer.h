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

	//glm::mat4 mModel;
	glm::mat4 mView;
	glm::mat4 mProj;

	std::vector<unsigned int> compiledShaderList;
	std::vector<Block> blockList;
	//Block *block1;

	unsigned int mVAO;
	unsigned int mEBO;

	unsigned int setupShaderProgram();
	int debugShader(unsigned int shader) const;
	unsigned int createShader(const char* path, GLenum type, bool debugShaderOpening);
	unsigned int compileShader(GLenum type, const GLchar* shader);
	unsigned int linkShaderProgram(unsigned int program, const std::vector<unsigned int> &shaders);
};
