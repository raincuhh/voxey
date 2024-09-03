#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>
#include <vector>
#include <memory>

#include "../../include/glad/glad.h"
#include "../../include/GLFW/glfw3.h"
#include "../../include/glm/glm.hpp"
#include "../utils/fileManager.h"
#include "shaderManager.h"

#include "chunkManager.h"
#include "camera.h"


namespace voxey::rendering
{
	class RenderingEngine
	{
	public:
		RenderingEngine(GLFWwindow* window);
		~RenderingEngine();

		void init();
		void renderUpdate(double dt) const;

		const glm::mat4& getViewMatrix() const;
		void setViewMatrix(const glm::mat4& viewMatrix);

		const glm::mat4& getProjMatrix() const;
		void setProjMatrix(const glm::mat4& projMatrix);

	private:
		GLFWwindow* mWindow;

		std::unique_ptr<voxey::rendering::ChunkManager> mChunkManager;
		std::unique_ptr<voxey::rendering::Camera> mCamera;

		voxey::rendering::ShaderManager* mShaderManager;
		GLuint mShaderProgram;

		glm::mat4 mViewMatrix;
		glm::mat4 mProjMatrix;

		//std::vector<Block> blockList;

		void setupShaderProgram();

		void updateShaderProjMatrix() const;
		void updateShaderViewMatrix() const;
	};
}