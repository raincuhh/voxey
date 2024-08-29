#pragma once

#include <vector>
#include <iostream>
#include <map>

#include "../../include/glad/glad.h"
#include "../../include/GLFW/glfw3.h"

#include "fileManager.h"

class ShaderManager
{
public:
	~ShaderManager();

	GLuint createProgram(const std::vector<std::pair<std::string, GLenum>>& shaderPaths);
	GLuint linkProgram(GLuint program, const std::vector<GLuint>& shaders);
	GLuint getActiveProgram();

private:
	GLuint createShader(const char* path, GLenum type);
	GLuint compileShader(const char* source, GLenum type);
	GLint debugShader(GLuint shader) const;
	GLint debugProgram(GLuint program) const;

	void deleteShadersFromActiveProgram();
	void deleteAllProgramShaders();


	std::map <GLuint, std::vector<GLuint>> programShaders;
};