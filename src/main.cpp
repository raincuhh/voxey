#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <memory>

#include "../src/core/application.h"


// ###########################################################
// ###                  welcome to main                    ###
// ###########################################################

int main(int argc, char** argv[])
{
	std::cout << "argc: " << argc << " argv: " << argv << std::endl;

	auto application = std::make_unique<Application>();
	return application->run();
}