#include "renderingEngine.h"

voxey::rendering::RenderingEngine::RenderingEngine(GLFWwindow* window) :
	mWindow(window),
	mChunkManager(nullptr),
	mCamera(nullptr),
	mShaderManager(nullptr),
	mShaderProgram(0),
	mViewMatrix(glm::mat4(1.0f)),
	mProjMatrix(glm::mat4(1.0f))
{
	init();
}

voxey::rendering::RenderingEngine::~RenderingEngine()
{
	if (mShaderManager)
	{
		mShaderManager->deleteShadersFromProgram(mShaderProgram);
		delete mShaderManager;
		mShaderManager = nullptr;
	}
}

void voxey::rendering::RenderingEngine::init()
{
	
	int chunkSize = 16;

	for (int x = 0; x < chunkSize; x++)
	{
		for (int y = 0; y < chunkSize; y++)
		{
			for (int z = 0; z < chunkSize; z++)
			{
				voxey::rendering::Block block(voxey::rendering::Block::BLOCK_TYPE_GRASS);
				block.translateModelMatrix(glm::vec3(x, y, z));
				blockList.push_back(block);
			}
		}
	}

	int width, height;
	glfwGetWindowSize(mWindow, &width, &height);

	mCamera = std::make_unique<voxey::rendering::Camera>(glm::vec3(0.0f, 0.0f, 3.0f), width, height, mWindow);

	mShaderManager = new voxey::rendering::ShaderManager();
	setupShaderProgram();
	if (mShaderProgram == 0)
	{
		std::cerr << "error failed shader program setup";
		return;
	}

	setProjMatrix(mCamera->getProjMatrix());

	mChunkManager = std::make_unique<voxey::rendering::ChunkManager>();
}

void voxey::rendering::RenderingEngine::renderUpdate(double deltaTime)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(mShaderProgram);

	mChunkManager->chunkListsUpdate(deltaTime);

	mCamera->cameraInputUpdate(deltaTime);
	mCamera->cameraUpdate(deltaTime);

	setViewMatrix(mCamera->getViewMatrix());
	
	for (Block block : blockList)
	{
		glm::mat4 modelMatrix = block.getModelMatrix();
		int modelLoc = glGetUniformLocation(mShaderProgram, "modelMatrix");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		block.draw(mShaderProgram);
	}
}

const glm::mat4& voxey::rendering::RenderingEngine::getViewMatrix() const
{
	return mViewMatrix;
}

const glm::mat4& voxey::rendering::RenderingEngine::getProjMatrix() const
{
	return mProjMatrix;
}

void voxey::rendering::RenderingEngine::setProjMatrix(const glm::mat4& projMatrix)
{
	mProjMatrix = projMatrix;
	updateShaderProjMatrix();
}

void voxey::rendering::RenderingEngine::setViewMatrix(const glm::mat4& viewMatrix)
{
	mViewMatrix = viewMatrix;
	updateShaderViewMatrix();
}

void voxey::rendering::RenderingEngine::setupShaderProgram()
{
	std::vector<std::pair<std::string, GLenum>> shaders = {
		{"shaders/vertexShader.vert", GL_VERTEX_SHADER},
		{"shaders/fragmentShader.frag", GL_FRAGMENT_SHADER}
		//
	};
	mShaderProgram = mShaderManager->createProgram(shaders);
}

void voxey::rendering::RenderingEngine::updateShaderProjMatrix() const
{
	voxey::rendering::ShaderManager::setUniformMat4fv(mShaderProgram, "projMatrix", mProjMatrix);
}

void voxey::rendering::RenderingEngine::updateShaderViewMatrix() const
{
	voxey::rendering::ShaderManager::setUniformMat4fv(mShaderProgram, "viewMatrix", mViewMatrix);
}
