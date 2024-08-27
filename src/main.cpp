#include "../src/core/application.h"
#include <memory>

// ###########################################################
// ###                  welcome to main                    ###
// ###########################################################
//
// if you get a fileManager::readFile("...") error. solution view > cmake targets view > voxey Project > 
// right click voxey(exectuable) > add "currentDir": "${workspaceRoot}" to the end of the json.



int main()
{
	auto application = std::make_unique<Application>();
	return application->run();
}