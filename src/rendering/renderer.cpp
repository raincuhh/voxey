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

	int viewLoc = glGetUniformLocation(mShaderProgram, "viewMatrix");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(mView));

	int projLoc = glGetUniformLocation(mShaderProgram, "projMatrix");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(mProj));

	for (Block block : blockList)
	{
		glm::mat4 modelMatrix = block.getModelMatrix();
		int modelLoc = glGetUniformLocation(mShaderProgram, "modelMatrix");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		block.draw(mShaderProgram);
	}
}

unsigned int Renderer::setupShaderProgram()
{
	bool debugSOpen = false;

	unsigned int vertexShader = createShader("shaders/vertexShader.vert", GL_VERTEX_SHADER, debugSOpen);
	unsigned int fragmentShader = createShader("shaders/fragmentShader.frag", GL_FRAGMENT_SHADER, debugSOpen);
	
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

unsigned int Renderer::compileShader(GLenum type, const GLchar* source)
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

unsigned int Renderer::createShader(const char* path, GLenum type, bool debugShaderOpening)
{
	std::string shaderSource = FileManager::readFile(path, debugShaderOpening);

	const char* parsedShaderSource = shaderSource.data();
	unsigned int vertexShader = compileShader(type, parsedShaderSource);

	return vertexShader;
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
