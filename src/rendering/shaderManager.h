#pragma once

#include <vector>
#include <iostream>
#include <map>

#include "../../include/glad/glad.h"
#include "../../include/GLFW/glfw3.h"
#include "../../include/glm/glm.hpp"
#include "../../include/glm/gtc/type_ptr.hpp"
#include "../utils/fileManager.h"

namespace voxey::rendering 
{
	class ShaderManager
	{
	public:
		~ShaderManager();

		GLuint createProgram(const std::vector<std::pair<std::string, GLenum>>& shaderPaths);
		static GLuint linkProgram(GLuint program, const std::vector<GLuint>& shaders);
		static GLuint getActiveProgram();

		static void setUniformMat4fv(GLuint program, const char* name, const glm::mat4& matrix);
		//
		void deleteShadersFromProgram(GLuint program);

	private:
		GLuint createShader(const char* path, GLenum type);
		GLuint compileShader(const char* source, GLenum type);
		GLint debugShader(GLuint shader) const;
		GLint debugProgram(GLuint program) const;

		void deleteShadersFromActiveProgram();
		void deleteAllProgramShaders();


		std::map <GLuint, std::vector<GLuint>> programShaders;
	};
}

