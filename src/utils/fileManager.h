#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

namespace voxey::utils
{
	class FileManager
	{
	public:
		static std::string readFile(const char* filePath, bool debug = false);
	};
}

