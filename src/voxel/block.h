#include <iostream>

#include "../../include/glm/glm.hpp"

#include "../../include/glad/glad.h"
#include "../../include/GLFW/glfw3.h"

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
	void draw(unsigned int shaderProgram) const;
private:
	BlockTypes mBlockType;
	GLuint mVAO;
	GLuint mVBO;
	GLuint mEBO;
	glm::vec3 fragColorValue;

	void setupMesh();
	glm::vec3 inferBlockType(BlockTypes type);
};