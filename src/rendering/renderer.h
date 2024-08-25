#pragma once

#include "../../include/glad/glad.h"
#include "../../include/GLFW/glfw3.h"

class Renderer
{
public:
	Renderer(GLFWwindow* window);
	~Renderer();

	void update(double dt);

private:
	GLFWwindow* mWindow;

	void setupShaders();
};
