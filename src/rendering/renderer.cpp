#include "renderer.h"

struct vertex {
	glm::vec3 position;
};

vertex vertices[] = {
	{{0.5f, 0.5f, 0.0f}}, //top left
	{{0.5f, -0.5f, 0.0f}}, // bottom left
	{{-0.5f, -0.5f, 0.0f}}, // bottom right
	{{-0.5f, 0.5f, 0.0f}}, // top right
};

unsigned int indicies[] = {
	0, 1, 3,
	1, 2, 3,
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
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	mVAO = VAO;

	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	mEBO = EBO;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

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

	float timeValue = glfwGetTime();
	float greenVal = (sin(timeValue) / 2.0f) + 0.5f;
	int vertexColLocation = glGetUniformLocation(mShaderProgram, "testColor");
	glUseProgram(mShaderProgram);
	glUniform3f(vertexColLocation, 0.0f, greenVal, 0.0f);
	glBindVertexArray(mVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	//glDrawArrays(GL_TRIANGLES, 0, 3);
	//glBindVertexArray(0);
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

		//std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << errorLog << std::endl;
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
