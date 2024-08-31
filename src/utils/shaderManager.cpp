#include "shaderManager.h"

Utils::ShaderManager::~ShaderManager()
{
	deleteAllProgramShaders();
}

GLuint Utils::ShaderManager::createProgram(const std::vector<std::pair<std::string, GLenum>>& shaderPaths)
{
	std::vector<GLuint> shaders;

	for (std::pair<std::string, GLenum> sInfo : shaderPaths)
	{
		GLuint shader = createShader(sInfo.first.c_str(), sInfo.second);
		shaders.push_back(shader);
	}

	GLuint shaderProgram = linkProgram(glCreateProgram(), shaders);

	programShaders[shaderProgram] = shaders;
	return shaderProgram;
}

GLuint Utils::ShaderManager::linkProgram(GLuint program, const std::vector<GLuint>& shaders)
{
	for (GLuint shader : shaders)
	{
		glAttachShader(program, shader);
	}

	glLinkProgram(program);

	GLint linked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if (linked == GL_FALSE)
	{
		GLint logLen = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLen);

		std::vector<GLchar> infoLog(logLen);
		glGetProgramInfoLog(program, logLen, &logLen, &infoLog[0]);
		glDeleteProgram(program);

		for (unsigned int shader : shaders)
		{
			glDeleteShader(shader);
		}
		return 0;
	}

	for (GLuint shader : shaders)
	{
		glDetachShader(program, shader);
	}

	return program;
}

GLuint Utils::ShaderManager::getActiveProgram()
{
	GLint program;
	glGetIntegerv(GL_CURRENT_PROGRAM, &program);
	return static_cast<GLuint>(program);
}

GLuint Utils::ShaderManager::createShader(const char* path, GLenum type)
{
	std::string source = Utils::FileManager::readFile(path);
	const char* parsedSource = source.data();

	GLuint shader = compileShader(parsedSource, type);
	return shader;
}
 
GLuint Utils::ShaderManager::compileShader(const char* source, GLenum type)
{
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	if (debugShader(shader) != EXIT_SUCCESS)
	{
		deleteShadersFromActiveProgram();
		return 0;
	}
	return shader;
}

GLint Utils::ShaderManager::debugShader(GLuint shader) const
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

GLint Utils::ShaderManager::debugProgram(GLuint program) const
{
	GLint shaderLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &shaderLinked);

	if (shaderLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> infoLog(maxLength);

		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
		glDeleteProgram(program);

		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

void Utils::ShaderManager::deleteShadersFromActiveProgram()
{
	GLuint activeProgram = getActiveProgram();

	if (programShaders.find(activeProgram) != programShaders.end())
	{
		for (GLuint shader : programShaders[activeProgram])
		{
			glDetachShader(activeProgram, shader);
			glDeleteShader(shader);
		}
		programShaders.erase(activeProgram);
	}
	else
	{
		std::cerr << "no shaders found for the active shader program" << std::endl;
	}
}

void Utils::ShaderManager::deleteAllProgramShaders()
{
	for (auto& entry : programShaders) 
	{
		GLuint program = entry.first;      
		std::vector<GLuint>& shaders = entry.second; 

		for (GLuint shader : shaders)
		{
			glDetachShader(program, shader);
			glDeleteShader(shader);  
		}

		glDeleteProgram(program);
	}

	programShaders.clear();  
}