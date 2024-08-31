#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
//#include <vector>

//#include "../core/logger.h"

namespace Utils 
{
	class FileManager
	{
	public:
		static std::string readFile(const char* filePath, bool debug = false);

	private:

	};
}

