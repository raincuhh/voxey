#include "chunkManager.h"

voxey::rendering::ChunkManager::ChunkManager()
{
}

voxey::rendering::ChunkManager::~ChunkManager()
{
}

void voxey::rendering::ChunkManager::chunkListsUpdate(double deltaTime)
{
	loadListUpdate();
	rebuildListUpdate();
	unloadListUpdate();
	visiblityListUpdate(/* will have camera to base visibilty off in the future */);
	//render list based on visiblity list.
}

void voxey::rendering::ChunkManager::loadListUpdate()
{
}

void voxey::rendering::ChunkManager::rebuildListUpdate()
{
}

void voxey::rendering::ChunkManager::unloadListUpdate()
{
}

void voxey::rendering::ChunkManager::visiblityListUpdate()
{
}
