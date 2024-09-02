#include "block.h"


struct vertex {
	glm::vec3 position;
	glm::vec2 textureCoords;
};

const vertex blockVertices[] = {
	// front
	{{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f }}, // top right
	{{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f }}, // bottom right
	{{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f }}, // bottom left
	{{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f }}, // top left

	// back
	{{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f }}, // top right
	{{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f }}, // bottom right
	{{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f }}, // bottom left
	{{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f }}, // top left

	// left
	{{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f }}, // top right
	{{-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f }}, // bottom right
	{{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f }}, // bottom left
	{{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f }}, // top left

	// right
	{{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f }}, // top right
	{{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f }}, // bottom right
	{{ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f }}, // bottom left
	{{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f }}, // top left

	// top
	{{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f }}, // top right
	{{ 0.5f,  0.5f, -0.5f}, {1.0f, 0.0f }}, // bottom right
	{{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f }}, // bottom left
	{{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f }}, // top left

	// bottom
	{{ 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f }}, // top right
	{{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f }}, // bottom right
	{{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f }}, // bottom left
	{{-0.5f, -0.5f,  0.5f}, {0.0f, 1.0f }}, // top left
	
};

const unsigned int indices[] = {
	// front
	0, 3, 1, // triangle1 
	1, 3, 2, // triangle2 

	// back
	4, 5, 7, // triangle1 
	5, 6, 7, // triangle2 

	// left
	8, 9, 11, // triangle1 
	9, 10, 11, // triangle2 

	// right
	12, 15, 13, // triangle1 
	13, 15, 14, // triangle2 

	// top
	16, 19, 17, // triangle1 
	17, 19, 18, // triangle2 

	// bottom
	20, 21, 23, // triangle1
	21, 22, 23, // triangle2
};

voxey::rendering::Block::Block(BlockTypes type)
{
	setType(type);

	setupMesh();
	setupTexture();
	setupModelMatrix();
}

voxey::rendering::Block::~Block()
{
}

void voxey::rendering::Block::draw([[maybe_unused]] unsigned int shaderProgram) const
{
	glBindTexture(GL_TEXTURE_2D, mTexture);
	glBindVertexArray(mVAO);

	glDrawElements(GL_TRIANGLES, sizeof(blockVertices), GL_UNSIGNED_INT, 0); // sizeof(blockVertices) / sizeof(unsigned int)
	glBindVertexArray(0);
}

void voxey::rendering::Block::setType(Block::BlockTypes type)
{
	mBlockType = type;
}

voxey::rendering::Block::BlockTypes voxey::rendering::Block::getType() const
{
	return mBlockType;
}

void voxey::rendering::Block::translateModelMatrix(glm::vec3 translate)
{
	modelMatrix = glm::translate(modelMatrix, glm::vec3(translate.x, translate.y, translate.z));
}

glm::mat4 voxey::rendering::Block::getModelMatrix() const
{
	return modelMatrix;
}

void voxey::rendering::Block::setupMesh()
{
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(blockVertices), blockVertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, position));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, textureCoords));
	glEnableVertexAttribArray(1);


	glGenBuffers(1, &mEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void voxey::rendering::Block::setupTexture()
{
	int success = voxey::utils::TextureLoader::LoadTexture("assets/testing/placeholder.png", mTexture);
	if (success != 1)
	{
		std::cerr << "error loading texture" << std::endl;
	}
}

void voxey::rendering::Block::setupModelMatrix()
{
	modelMatrix = glm::rotate(modelMatrix, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, 5.0f));
}
