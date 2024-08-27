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
	Block block1(BlockTypeGrass);
	blockList.push_back(block1);


	mShaderProgram = setupShaderProgram();
	if (mShaderProgram == 0)
	{
		std::cerr << "error failed shader program setup";
		return;
	}

	glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);

	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::rotate(modelMatrix, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	mModel = modelMatrix;

	glm::mat4 viewMatrix = glm::mat4(1.0f);
	viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));
	mView = viewMatrix;

	int width, height;
	glfwGetWindowSize(mWindow, &width, &height);
	float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
	constexpr float fov = glm::radians(90.0f);

	glm::mat4 projMatrix = glm::perspective(fov, aspectRatio, 0.1f, 100.0f);
	mProj = projMatrix;
}

void Renderer::renderUpdate(double dt) const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(mShaderProgram);

	int modelLoc = glGetUniformLocation(mShaderProgram, "model");
	glUniformMatrix4fv(mShaderProgram, 1, GL_FALSE, glm::value_ptr(mModel));

	int viewLoc = glGetUniformLocation(mShaderProgram, "view");
	glUniformMatrix4fv(mShaderProgram, 1, GL_FALSE, glm::value_ptr(mView));

	int projLoc = glGetUniformLocation(mShaderProgram, "projection");
	glUniformMatrix4fv(mShaderProgram, 1, GL_FALSE, glm::value_ptr(mProj));


	for (Block block : blockList)
	{
		block.draw(mShaderProgram);
	}
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
