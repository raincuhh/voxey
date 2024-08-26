#include <iostream>

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
	Block();
	~Block();
private:
	uint8_t mBlockType = BlockTypeAir;

};