#pragma once

#include <iostream>
#include <map>
#include <functional>
#include <string>

using Name = std::string;
using Callback = std::function<void()>;

namespace voxey::core
{
	class UpdateManager
	{
	public:
		static void registerUpdateFunc(const Name& name, Callback func);
		static void unRegisterUpdateFunc(const Name& name);
		static void processUpdate();

	private:
		static std::map<Name, Callback> processUpdateFunctions;
	};
}