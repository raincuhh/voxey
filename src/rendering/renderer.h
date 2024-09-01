#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>
#include <vector>
#include <memory>

#include "../utils/graphicsManager.h"
#include "../../include/glm/glm.hpp"
#include "../utils/shaderManager.h"
#include "../utils/fileManager.h"
#include "block.h"


namespace Rendering {
	class Renderer
	{
	public:
		Renderer(GLFWwindow* window);
		~Renderer();

		void init();
		void renderUpdate(double dt) const;

		const glm::mat4& getViewMatrix() const;
		void setViewMatrix(const glm::mat4& viewMatrix);

		const glm::mat4& getProjMatrix() const;
		void setProjMatrix(const glm::mat4& projMatrix);

	private:
		GLFWwindow* mWindow;
		Utils::ShaderManager* mShaderManager;
		GLuint mShaderProgram;
		glm::mat4 mViewMatrix;
		glm::mat4 mProjMatrix;

		std::vector<unsigned int> compiledShaderList;
		std::vector<Block> blockList;

		void setupShaderProgram();

		void updateShaderProjMatrix() const;
		void updateShaderViewMatrix() const;
	};
}