#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "../../include/glad/glad.h"
#include "../../include/GLFW/glfw3.h"

#include "chunk.h"
#include "block.h"


namespace voxey::rendering 
{
	class ChunkManager
	{
	public:
		ChunkManager();
		~ChunkManager();

		void chunkListsUpdate(double deltaTime);
		// eventually add async loading for chunks using multithreading.

	private:
		void loadListUpdate();
		void rebuildListUpdate();
		void unloadListUpdate();
		void visiblityListUpdate();

		//todo add the lists here
	};
}

