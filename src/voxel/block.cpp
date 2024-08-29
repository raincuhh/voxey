#include "block.h"


struct vertex {
	glm::vec3 position;
	glm::vec2 textureCoords;
};

const vertex cubeVertices[] = {

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
	0, 1, 3, // triangle1 
	1, 2, 3, // triangle2 

	// back
	4, 7, 5, // triangle1 
	5, 7, 6, // triangle2 

	// left
	8, 11, 9, // triangle1 
	9, 11, 10, // triangle2 

	// right
	12, 13, 15, // triangle1 
	13, 14, 15, // triangle2 

	// top
	16, 17, 19, // triangle1 
	17, 18, 19, // triangle2 

	// bottom
	20, 23, 21, // triangle1
	21, 23, 22, // triangle2
	
};

Block::Block(BlockTypes type)
{
	setType(type);
	fragColorValue = inferBlockType(type);

	setupMesh();
	setupTexture(); //currently renders some weird line strip texture
	setupModelMatrix();
}

Block::~Block()
{
}

void Block::draw([[maybe_unused]] unsigned int shaderProgram) const
{
	glBindTexture(GL_TEXTURE_2D, mTexture);

	glBindVertexArray(mVAO);
	glDrawElements(GL_TRIANGLES, sizeof(cubeVertices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Block::setType(Block::BlockTypes type)
{
	mBlockType = type;
}

Block::BlockTypes Block::getType() const
{
	return mBlockType;
}

void Block::translateModelMatrix(glm::vec3 translate)
{
	modelMatrix = glm::translate(modelMatrix, glm::vec3(translate.x, translate.y, translate.z));
}

glm::mat4 Block::getModelMatrix() const
{
	return modelMatrix;
}

void Block::setupMesh()
{
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, position));//3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, textureCoords)); //(void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &mEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void Block::setupTexture()
{
	int success = TextureLoader::LoadTexture("assets/testing/placeholder.png", mTexture);
	if (success != 1)
	{
		std::cerr << "error loading texture" << std::endl;
	}
}

void Block::setupModelMatrix()
{
	modelMatrix = glm::rotate(modelMatrix, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, 5.0f));
}


glm::vec3 Block::inferBlockType(BlockTypes type)
{
	switch (type)
	{
	case BLOCK_TYPE_AIR:
		return glm::vec3(0.0f, 0.0f, 0.0f);
		break;
	case BLOCK_TYPE_GRASS:
		return glm::vec3(0.0f, 2.0f, 0.0f);
		break;
	case BLOCK_TYPE_DIRT:
		return glm::vec3(0.5f, 0.35f, 0.05f);
		break;
	case BLOCK_TYPE_STONE:
		return glm::vec3(0.7f, 0.7f, 0.7f);
		break;
	//case BLOCK_TYPE_SAND:
	//	return glm::vec3();
	//	break;
	//case BLOCK_TYPE_WOOD:
	//	return glm::vec3();
	//	break;
	default:
		return glm::vec3(0.0f, 0.0f, 0.0f);
		break;
	}
}
