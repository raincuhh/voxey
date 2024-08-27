#include "block.h"

struct vertex {
	glm::vec3 position;
	//glm::vec2 texCoords;
};

vertex vertices[] = {

	//face front
	{{0.5f, 0.5f, 0.0f}}, //top left
	{{0.5f, -0.5f, 0.0f}}, // bottom left
	{{-0.5f, -0.5f, 0.0f}}, // bottom right
	{{-0.5f, 0.5f, 0.0f}}, // top right
};

unsigned int indicies[] = {
	//face front
	0, 1, 3, //triangle1
	1, 2, 3, //triangle2
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
	glDrawElements(GL_TRIANGLES, sizeof(vertices), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Block::setupMesh()
{
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	glGenBuffers(1, &mVBO);

	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &mEBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);
}

glm::vec3 Block::inferBlockType(BlockTypes type)
{
	switch (type)
	{
	case BlockTypeAir:
		return glm::vec3(0.0f, 0.0f, 0.0f);
		break;
	case BlockTypeGrass:
		return glm::vec3(0.0f, 1.0f, 0.0f);
		break;
	case BlockTypeDirt:
		return glm::vec3(0.5f, 0.35f, 0.05f);
		break;
	case BlockTypeStone:
		return glm::vec3(0.7f, 0.7f, 0.7f);
		break;
	case BlockTypeSand:
		return glm::vec3();
		break;
	case BlockTypeWood:
		return glm::vec3();
		break;
	default:
		break;
	}
}
