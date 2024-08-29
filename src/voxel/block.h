#pragma once

#include <iostream>

#include "../../include/glm/glm.hpp"
#include <../../include/glm/gtc/matrix_transform.hpp>
#include <../../include/glm/gtc/type_ptr.hpp>

#include "../../include/glad/glad.h"
#include "../../include/GLFW/glfw3.h"

#include "../utils/textureLoader.h"

class Block
{
public:
	enum BlockTypes : uint8_t {
		BLOCK_TYPE_AIR = 0,
		BLOCK_TYPE_GRASS = 1,
		BLOCK_TYPE_DIRT = 2,
		BLOCK_TYPE_STONE = 3,
		BLOCK_TYPE_SAND = 4,
		BLOCK_TYPE_WOOD = 5,
	};

	Block(BlockTypes type);
	~Block();

	void draw(unsigned int shaderProgram) const;

	void setType(BlockTypes type);
	BlockTypes getType() const;

	void translateModelMatrix(glm::vec3 translate);
	glm::mat4 getModelMatrix() const;
private:
	BlockTypes mBlockType;
	GLuint mVAO;
	GLuint mVBO;
	GLuint mEBO;
	GLuint mTexture;
	glm::vec3 fragColorValue;
	glm::mat4 modelMatrix = glm::mat4(1.0f);

	void setupMesh();
	void setupTexture();
	void setupModelMatrix();
	glm::vec3 inferBlockType(BlockTypes type);
};