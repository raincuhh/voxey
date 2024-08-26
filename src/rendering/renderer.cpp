#include "renderer.h"

float vertices[9] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f,
};

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* vertexShaderTest;

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

	char buffer[256];
	if (_getcwd(buffer, sizeof(buffer)) == NULL) 
	{
		std::cerr << "error gettign current working directory" << std::endl;
		return;
	}

	std::cout << "current working directory" << buffer << std::endl;

	std::string vertexText;
	//relative path stil doesnt work, absolute does
	//std::ifstream vertFile("C:/dev/repos/voxey/shaders/vertexShader.vert");
	std::ifstream vertFile("../../../../shaders/vertexShader.vert");

	if (!vertFile.is_open())
	{
		std::cerr << "failed opening vertFile for reading" << std::endl;
		return;
	}

	while (std::getline(vertFile, vertexText)) {
		std::cout << vertexText << std::endl;
	}
	vertFile.close();

}

void Renderer::update(double dt)
{
}

void Renderer::setupShaders()
{
}
