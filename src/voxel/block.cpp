#include "block.h"

struct vertex {
	glm::vec3 position;
	//glm::vec2 texCoords;
};

vertex cubeVertices[] = {

	// Face front
	{{ 0.5f,  0.5f,  0.5f}}, // top right
	{{ 0.5f, -0.5f,  0.5f}}, // bottom right
	{{-0.5f, -0.5f,  0.5f}}, // bottom left
	{{-0.5f,  0.5f,  0.5f}}, // top left

	/*
	// Face back
	{{ 0.5f,  0.5f, -0.5f}}, // top right
	{{ 0.5f, -0.5f, -0.5f}}, // bottom right
	{{-0.5f, -0.5f, -0.5f}}, // bottom left
	{{-0.5f,  0.5f, -0.5f}}, // top left

	// Face left
	{{-0.5f,  0.5f,  0.5f}}, // top right
	{{-0.5f, -0.5f,  0.5f}}, // bottom right
	{{-0.5f, -0.5f, -0.5f}}, // bottom left
	{{-0.5f,  0.5f, -0.5f}}, // top left

	// Face right
	{{ 0.5f,  0.5f,  0.5f}}, // top right
	{{ 0.5f, -0.5f,  0.5f}}, // bottom right
	{{ 0.5f, -0.5f, -0.5f}}, // bottom left
	{{ 0.5f,  0.5f, -0.5f}}, // top left

	// Face top
	{{ 0.5f,  0.5f,  0.5f}}, // top right
	{{ 0.5f,  0.5f, -0.5f}}, // bottom right
	{{-0.5f,  0.5f, -0.5f}}, // bottom left
	{{-0.5f,  0.5f,  0.5f}}, // top left

	// Face bottom
	{{ 0.5f, -0.5f,  0.5f}}, // top right
	{{ 0.5f, -0.5f, -0.5f}}, // bottom right
	{{-0.5f, -0.5f, -0.5f}}, // bottom left
	{{-0.5f, -0.5f,  0.5f}}, // top left
	*/
};

unsigned int indices[] = {
	// Face front
	0, 1, 3, // triangle1 
	1, 2, 3, // triangle2 

	/*
	// Face back
	4, 7, 5, // triangle1 
	5, 7, 6, // triangle2 

	// Face left
	8, 11, 9, // triangle1 
	9, 11, 10, // triangle2 

	// Face right
	12, 13, 15, // triangle1 
	13, 14, 15, // triangle2 

	// Face top
	16, 17, 19, // triangle1 
	17, 18, 19, // triangle2 

	// Face bottom
	20, 23, 21, // triangle1
	21, 23, 22, // triangle2
	*/
};

float texCoords[] = {
	0.0f, 0.0f,
	1.0f, 0.0f,
	0.5f, 1.0f
};

Block::Block(BlockTypes type)
{
	setType(type);
	setupMesh();
	fragColorValue = inferBlockType(type);
}

Block::~Block()
{
}

void Block::setType(BlockTypes type)
{
}

BlockTypes Block::getType() const
{
	return mBlockType;
}

void Block::draw(unsigned int shaderProgram) const
{
	int fragLocation = glGetUniformLocation(shaderProgram, "uniformFragColor");
	glUniform3f(fragLocation, fragColorValue.x, fragColorValue.y, fragColorValue.y);

	glBindVertexArray(mVAO);
	glDrawElements(GL_TRIANGLES, sizeof(cubeVertices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Block::setupMesh()
{
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	glGenBuffers(1, &mVBO);

	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &mEBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

glm::vec3 Block::inferBlockType(BlockTypes type)
{
	switch (type)
	{
	case BlockTypeAir:
		return glm::vec3(0.0f, 0.0f, 0.0f);
		break;
	case BlockTypeGrass:
		return glm::vec3(0.0f, 2.0f, 0.0f);
		break;
	case BlockTypeDirt:
		return glm::vec3(0.5f, 0.35f, 0.05f);
		break;
	case BlockTypeStone:
		return glm::vec3(0.7f, 0.7f, 0.7f);
		break;
	//case BlockTypeSand:
	//	return glm::vec3();
	//	break;
	//case BlockTypeWood:
	//	return glm::vec3();
	//	break;
	default:
		return glm::vec3(0.0f, 0.0f, 0.0f);
		break;
	}
}
