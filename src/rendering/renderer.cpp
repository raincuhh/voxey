#include "renderer.h"

Renderer::Renderer(GLFWwindow* window) : mWindow(window)
{
	init();
}

Renderer::~Renderer()
{
	for (unsigned int shader : compiledShaderList)
	{
		glDeleteShader(shader);
	}

	glDeleteBuffers(1, &mVAO);
	glDeleteBuffers(1, &mEBO);
}

void Renderer::init() 
{
	Block block1(Block::BLOCK_TYPE_GRASS);
	blockList.push_back(block1);

	mShaderManager = new ShaderManager();

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

	viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -10.0f));
	mView = viewMatrix;

	projMatrix = glm::perspective(fov, aspectRatio, 0.1f, 100.0f);
	mProj = projMatrix;

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
	glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
	glm::mat4 view;
	view = glm::lookAt(
		glm::vec3(0.0f, 0.0f, 3.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);

}

void Renderer::renderUpdate(double dt) const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(mShaderProgram);

	int viewLoc = glGetUniformLocation(mShaderProgram, "viewMatrix");
	int projLoc = glGetUniformLocation(mShaderProgram, "projMatrix");

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(mView));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(mProj));


	//glm::mat4 view = glm::mat4(1.0f); // fix the view shit
	//float radius = 10.0f;
	//float camX = static_cast<float>(sin(glfwGetTime()) * radius);
	//float camZ = static_cast<float>(cos(glfwGetTime()) * radius);
	//view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	for (Block block : blockList)
	{
		glm::mat4 modelMatrix = block.getModelMatrix();
		int modelLoc = glGetUniformLocation(mShaderProgram, "modelMatrix");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		block.draw(mShaderProgram);
	}
}

void Renderer::setupShaderProgram()
{
	std::vector<std::pair<std::string, GLenum>> shaders = {
		{"shaders/vertexShader.vert", GL_VERTEX_SHADER},
		{"shaders/fragmentShader.frag", GL_FRAGMENT_SHADER}
		//
	};

	mShaderProgram = mShaderManager->createProgram(shaders);
}