#define STB_IMAGE_IMPLEMENTATION
#include <memory>

#include "../src/core/application.h"


// ###########################################################
// ###                  welcome to main                    ###
// ###########################################################

int main()
{
	auto application = std::make_unique<Application>();
	return application->run();
}