#define STB_IMAGE_IMPLEMENTATION
#include <memory>
#include "application.h"

int main(int argc, char** argv[])
{
	auto application = std::make_unique<voxey::core::Application>(argc, argv);
	return application->run();
}