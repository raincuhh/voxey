#define STB_IMAGE_IMPLEMENTATION
#include <memory>
#include "../src/core/application.h"

int main(int argc, char** argv[])
{
	auto application = std::make_unique<Application>(argc, argv);
	return application->run();
}