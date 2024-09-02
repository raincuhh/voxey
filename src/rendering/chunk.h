#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "block.h"
#include "chunkManager.h"

namespace voxey::rendering
{
	class Chunk
	{
	public:
		Chunk();
		~Chunk();

		//void buildChunkMesh();
		//void renderChunk();
		//void getBlock(int x, int y, int z);

	private:
		int chunkSize = 16;
		int blockSize = chunkSize / chunkSize;
		//std::vector<voxey::rendering::Block> blocks;
	};
}

