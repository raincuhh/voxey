#pragma once

#include <iostream>
#include <vector>

#include "block.h"
#include "chunkManager.h"


class Chunk
{
public:
	Chunk();
	~Chunk();
	
	void buildChunk();
	void renderChunk();

private:
	int chunkSize = 16;
	std::vector<voxey::rendering::Block> blocks;
};