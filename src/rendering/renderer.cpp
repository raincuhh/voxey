#include "renderer.h"

float vertices[9] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f,
};

Renderer::Renderer(GLFWwindow* window) : mWindow(window)
{
	init();
}

Renderer::~Renderer()
{
}

void Renderer::init()
{
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	setupShaders();
}

void Renderer::update(double dt)
{
}

void Renderer::setupShaders()
{
	//vertex shader
	std::string vertexShaderSource = FileManager::readFile("shaders/vertexShader.vert").c_str();
	std::cout << vertexShaderSource << std::endl;
	


}
