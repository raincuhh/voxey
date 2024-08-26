#include <iostream>

#include "../../include/glad/glad.h"
#include "../../include/GLFW/glfw3.h"

enum BlockTypes {
	BlockTypeDefault = 0,
	BlockTypeGrass,
	BlockTypeDirt,
	BlockTypeStone,
	BlockTypeSand,
	BlockTypeWood,
};

class Block
{
public:
	Block();
	~Block();
	bool isActive();
	void setActive(bool active);
private:
	bool mActive;
	BlockTypes mBlockType = BlockTypeDefault;

};