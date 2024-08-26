#include "../src/core/application.h"
#include <memory>

int main()
{
	auto application = std::make_unique<Application>();
	return application->run();
}