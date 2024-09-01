#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <memory>
#include "../src/core/application.h"

int main(int argc, char** argv[])
{
	std::cout << "argc: " << argc << " argv: " << argv << std::endl;

	auto application = std::make_unique<EntryPoint::Application>();
	return application->run();
}