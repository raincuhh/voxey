#include "../src/core/application.h"
#include <memory>


//note to self, working directory is relative to the executable, not project
int main()
{
	auto application = std::make_unique<Application>();
	return application->run();
}