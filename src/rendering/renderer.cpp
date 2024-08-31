#include "renderer.h"

Rendering::Renderer::Renderer(GLFWwindow* window) : mWindow(window)
{
	init();
}

Rendering::Renderer::~Renderer()
{
	for (unsigned int shader : compiledShaderList)
	{
		glDeleteShader(shader);
	}

	glDeleteBuffers(1, &mVAO);
	glDeleteBuffers(1, &mEBO);
}

void Rendering::Renderer::init()
{
	int blockRenderSize = 16;

	for (int x = 0; x < 16; x++)
	{
		for (int y = 0; y < 16; y++)
		{
			for (int z = 0; z < 16; z++)
			{
				Rendering::Block block(Block::BLOCK_TYPE_GRASS);
				block.translateModelMatrix(glm::vec3(x, y, z));
				blockList.push_back(block);
			}
		}
	}


	//Block block1(Block::BLOCK_TYPE_GRASS);
	//blockList.push_back(block1);

	mShaderManager = new Utils::ShaderManager();

	setupShaderProgram();
	if (mShaderProgram == 0)
	{
		std::cerr << "error failed shader program setup";
		return;
	}

	int width, height;
	glfwGetWindowSize(mWindow, &width, &height);

	float aspectRatio = static_cast<float>(width) / static_cast<float>(height);

	constexpr float fov = glm::radians(45.0f);

	glm::mat4 viewMatrix = glm::mat4(1.0f);
	glm::mat4 projMatrix = glm::mat4(1.0f);

	// change this shit
	viewMatrix = glm::translate(viewMatrix, glm::vec3(-5.0f, -10.0f, -30.0f));
	mView = viewMatrix;

	projMatrix = glm::perspective(fov, aspectRatio, 0.1f, 100.0f);
	mProj = projMatrix;

	glUseProgram(mShaderProgram);
	int projLoc = glGetUniformLocation(mShaderProgram, "projMatrix");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(mProj));
}

void Rendering::Renderer::renderUpdate(double deltaTime) const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(mShaderProgram);

	//not really worth having projMatrix being set every update because it rarely gets changed anyways
	int viewLoc = glGetUniformLocation(mShaderProgram, "viewMatrix");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(mView));


	for (Block block : blockList)
	{
		glm::mat4 modelMatrix = block.getModelMatrix();
		int modelLoc = glGetUniformLocation(mShaderProgram, "modelMatrix");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		block.draw(mShaderProgram);
	}
}

void Rendering::Renderer::setupShaderProgram()
{
	std::vector<std::pair<std::string, GLenum>> shaders = {
		{"shaders/vertexShader.vert", GL_VERTEX_SHADER},
		{"shaders/fragmentShader.frag", GL_FRAGMENT_SHADER}
		//
	};

	mShaderProgram = mShaderManager->createProgram(shaders);
}