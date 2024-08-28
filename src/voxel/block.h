#pragma once

#include <iostream>

#include "../../include/glm/glm.hpp"
#include <../../include/glm/gtc/matrix_transform.hpp>
#include <../../include/glm/gtc/type_ptr.hpp>

#include "../../include/glad/glad.h"
#include "../../include/GLFW/glfw3.h"

#include "../../include/stb-master/stb_image.h"

enum BlockTypes : uint8_t {
	BlockTypeAir = 0,
	BlockTypeGrass = 1,
	BlockTypeDirt = 2,
	BlockTypeStone = 3,
	BlockTypeSand = 4,
	BlockTypeWood = 5,
};

class Block
{
public:
	Block(BlockTypes type);
	~Block();

	void setType(BlockTypes type);
	BlockTypes getType() const;
	glm::mat4 getModelMatrix() const;
	void draw(unsigned int shaderProgram) const;
private:
	BlockTypes mBlockType;
	GLuint mVAO;
	GLuint mVBO;
	GLuint mEBO;
	GLuint mTexture;
	glm::vec3 fragColorValue;
	glm::mat4 modelMatrix = glm::mat4(1.0f);

	//vertex *cubeVertices;

	void setupMesh();
	void setupTexture();
	void setupModelMatrix();
	glm::vec3 inferBlockType(BlockTypes type);
};