#include "renderer.h"

Renderer::Renderer(GLFWwindow* window) : mWindow(window)
{
	init();
}

Renderer::~Renderer()
{
}

void Renderer::init()
{

	block1 = new Block(BlockTypeDirt);

	mShaderProgram = setupShaderProgram();
	if (mShaderProgram == 0)
	{
		std::cerr << "error failed shader program setup";
		return;
	}
}

void Renderer::renderUpdate(double dt) const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(mShaderProgram);


	block1->draw(mShaderProgram);
}

unsigned int Renderer::setupShaderProgram()
{
	bool debugShaderOpening = false;

	//vertex shader
	std::string vertexShaderCode = FileManager::readFile("shaders/vertexShader.vert", debugShaderOpening);
	const char* vertexShaderSource = vertexShaderCode.data();
	unsigned int vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSource);

	//fragment shader
	std::string fragmentShaderCode = FileManager::readFile("shaders/fragmentShader.frag", debugShaderOpening);
	const char* fragmentShaderSource = fragmentShaderCode.data();
	unsigned int fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
	
	unsigned int shaderProgram = glCreateProgram();
	linkShaderProgram(shaderProgram, compiledShaderList);
	
	return shaderProgram;
}

int Renderer::debugShader(unsigned int shader) const
{
	GLint compiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (compiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

unsigned int Renderer::createShader(GLenum type, const GLchar* source)
{
	unsigned int shader = glCreateShader(type);

	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);


	if (debugShader(shader) != EXIT_SUCCESS)
	{
		glDeleteShader(shader);

		for (unsigned int compiledShader : compiledShaderList)
		{
			glDeleteShader(compiledShader);
		}
		compiledShaderList.clear();

		return 0;
	}

	compiledShaderList.push_back(shader);
	return shader;
}

unsigned int Renderer::linkShaderProgram(unsigned int program, const std::vector<unsigned int>& shaders)
{
	for (unsigned int shader : shaders)
	{
		glAttachShader(program, shader);
	}

	glLinkProgram(program);
	GLint shaderLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &shaderLinked);

	if (shaderLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

		glDeleteProgram(program);
		for (unsigned int shader : shaders)
		{
			glDeleteShader(shader);
		}
		return 0;
	}

	for (unsigned int shader : shaders)
	{
		glDetachShader(program, shader);
	}

	return program;
}
