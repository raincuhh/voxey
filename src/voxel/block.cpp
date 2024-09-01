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

Rendering::Block::Block(BlockTypes type)
{
	setType(type);
	fragColorValue = inferBlockType(type);

	setupMesh();
	setupTexture();
	setupModelMatrix();
}

Rendering::Block::~Block()
{
}

void Rendering::Block::draw([[maybe_unused]] unsigned int shaderProgram) const
{
	GraphicsManager::bindTexture(GL_TEXTURE_2D, mTexture);
	GraphicsManager::bindVertexArray(mVAO);

	GraphicsManager::drawElements(GL_TRIANGLES, sizeof(blockVertices), GL_UNSIGNED_INT, 0); // sizeof(blockVertices) / sizeof(unsigned int)
	GraphicsManager::bindVertexArray(0);
}

void Rendering::Block::setType(Block::BlockTypes type)
{
	mBlockType = type;
}

Rendering::Block::BlockTypes Rendering::Block::getType() const
{
	return mBlockType;
}

void Rendering::Block::translateModelMatrix(glm::vec3 translate)
{
	modelMatrix = glm::translate(modelMatrix, glm::vec3(translate.x, translate.y, translate.z));
}

glm::mat4 Rendering::Block::getModelMatrix() const
{
	return modelMatrix;
}

void Rendering::Block::setupMesh()
{
	GraphicsManager::genVertexArrays(1, &mVAO);
	GraphicsManager::bindVertexArray(mVAO);

	GraphicsManager::genBuffers(1, &mVBO);
	GraphicsManager::bindBuffer(GL_ARRAY_BUFFER, mVBO);
	GraphicsManager::bufferData(GL_ARRAY_BUFFER, sizeof(blockVertices), blockVertices, GL_STATIC_DRAW);
	
	GraphicsManager::vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, position));
	GraphicsManager::enableVertexAttribArray(0);

	GraphicsManager::vertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, textureCoords));
	GraphicsManager::enableVertexAttribArray(1);

	GraphicsManager::genBuffers(1, &mEBO);
	GraphicsManager::bindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	GraphicsManager::bufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	GraphicsManager::bindVertexArray(0);
}

void Rendering::Block::setupTexture()
{
	int success = Utils::TextureLoader::LoadTexture("assets/testing/placeholder.png", mTexture);
	if (success != 1)
	{
		std::cerr << "error loading texture" << std::endl;
	}
}

void Rendering::Block::setupModelMatrix()
{
	modelMatrix = glm::rotate(modelMatrix, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, 5.0f));
}


glm::vec3 Rendering::Block::inferBlockType(BlockTypes type)
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
