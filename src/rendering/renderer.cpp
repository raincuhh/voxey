#include "renderer.h"

float vertices[] = {
	0.5f, 0.5f, 0.0f, // top left
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f, //top right
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
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	mEBO = EBO;

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	mVAO = VAO;

	unsigned int VBO;
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

	unsigned int shaderProgram = setupShaderProgram();
	if (shaderProgram == 0)
	{
		std::cerr << "error failed shader program setup";
		return;
	}
	else
	{
		mShaderProgram = shaderProgram;
	}

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void Renderer::update(double dt) const
{
	glUseProgram(mShaderProgram);
	glBindVertexArray(mVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	//glBindVertexArray(0);
}

unsigned int Renderer::setupShaderProgram()
{
	//vertex shader
	std::string vertexShaderCode = FileManager::readFile("shaders/vertexShader.vert");
	const char* vertexShaderSource = vertexShaderCode.c_str();
	
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	if (debugShader(vertexShader) != EXIT_SUCCESS)
	{
		glDeleteShader(vertexShader);
		return 0;
		
	}

	//fragment shader
	std::string fragmentShaderCode = FileManager::readFile("shaders/fragmentShader.frag");
	const char* fragmentShaderSource = fragmentShaderCode.c_str();

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	if (debugShader(fragmentShader) != EXIT_SUCCESS)
	{
		// delete both shaders, as in frag and vert cause we dont want memory leak.
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		return 0;
	}

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	GLint shaderLinked = 0;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &shaderLinked);
	if (shaderLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(shaderProgram, maxLength, &maxLength, &infoLog[0]);

		glDeleteProgram(shaderProgram);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		return 0;
	}

	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);
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

		//std::cerr << maxLength;
		//std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << errorLog << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}