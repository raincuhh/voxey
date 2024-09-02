#include "fileManager.h"


std::string voxey::utils::FileManager::readFile(const char* filePath, bool debug)
{
	std::string content = "";
	std::ifstream file(filePath);

	if (debug)
	{
		std::cout << "Trying to open file: " << std::filesystem::absolute(filePath) << std::endl;
	}
	
	if (!file.is_open())
	{
		std::cerr << "error opening " << filePath << " for reading" << std::endl;
		return content;
	}

	std::string line;
	while (std::getline(file, line))
	{
		content += line + "\n";
	}
	return content;
}