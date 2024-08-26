#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>

#include "../../include/glad/glad.h"
#include "../../include/GLFW/glfw3.h"

#include "../utils/fileManager.h"

class Renderer
{
public:
	Renderer(GLFWwindow* window);
	~Renderer();
	void init();

	void update(double dt);

private:
	GLFWwindow* mWindow;

	unsigned int vertexShader;

	void setupShaders();
};
