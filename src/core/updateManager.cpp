#include "updateManager.h"

std::map<Name, Callback> voxey::core::UpdateManager::processUpdateFunctions;

void voxey::core::UpdateManager::registerUpdateFunc(const Name& name, Callback func)
{
	processUpdateFunctions[name] = func;
}

void voxey::core::UpdateManager::unRegisterUpdateFunc(const Name& name)
{
	processUpdateFunctions.erase(name);
}

void voxey::core::UpdateManager::processUpdate()
{
	if (processUpdateFunctions.empty()) return;
	for (const auto& pair : processUpdateFunctions)
	{
		pair.second();
	}
}
