#include "renderer.h"

Rendering::Renderer::Renderer(GLFWwindow* window) :
	mWindow(window),
	mShaderManager(nullptr),
	mShaderProgram(0),
	mViewMatrix(glm::mat4(1.0f)),
	mProjMatrix(glm::mat4(1.0f)),
	compiledShaderList(0)
{
	init();
}

Rendering::Renderer::~Renderer()
{
	for (unsigned int shader : compiledShaderList)
	{
		glDeleteShader(shader);
	}
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

	mShaderManager = new Utils::ShaderManager();

	setupShaderProgram();
	if (mShaderProgram == 0)
	{
		std::cerr << "error failed shader program setup";
		return;
	}

	int width;
	int height;
	float aspectRatio;
	constexpr float fov = glm::radians(45.0f);

	glfwGetWindowSize(mWindow, &width, &height);
	aspectRatio = static_cast<float>(width) / static_cast<float>(height);

	setViewMatrix(glm::translate(mViewMatrix, glm::vec3(-5.0f, -10.0f, -30.0f)));
	setProjMatrix(glm::perspective(fov, aspectRatio, 0.1f, 100.0f));
}

void Rendering::Renderer::renderUpdate(double deltaTime) const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(mShaderProgram);

	updateShaderViewMatrix();


	for (Block block : blockList)
	{
		glm::mat4 modelMatrix = block.getModelMatrix();
		int modelLoc = glGetUniformLocation(mShaderProgram, "modelMatrix");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		block.draw(mShaderProgram);
	}
}

const glm::mat4& Rendering::Renderer::getViewMatrix() const
{
	return mViewMatrix;
}

void Rendering::Renderer::setViewMatrix(const glm::mat4& viewMatrix)
{
	mViewMatrix = viewMatrix;
	updateShaderViewMatrix();
}

const glm::mat4& Rendering::Renderer::getProjMatrix() const
{
	return mProjMatrix;
}

void Rendering::Renderer::setProjMatrix(const glm::mat4& projMatrix)
{
	mProjMatrix = projMatrix;
	updateShaderProjMatrix();
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

void Rendering::Renderer::updateShaderProjMatrix() const
{
	Utils::ShaderManager::setUniformMat4fv(mShaderProgram, "projMatrix", mProjMatrix);
}

void Rendering::Renderer::updateShaderViewMatrix() const
{
	Utils::ShaderManager::setUniformMat4fv(mShaderProgram, "viewMatrix", mViewMatrix);
}
