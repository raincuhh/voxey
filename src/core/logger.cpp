#include "logger.h"

Voxey::Core::Logger::Logger()
{
}

Voxey::Core::Logger::~Logger()
{
}

void Voxey::Core::Logger::run()
{
    std::cout << "running logger" << std::endl;
    //TODO: just so i can remember, i changed from mingw to msvc lib to fix it
	glfwSetErrorCallback(glfwErrorCallback); 
}

void Voxey::Core::Logger::glfwErrorCallback(int err, const char* desc)
{
	std::cerr << "GLFW error '" << err << "': " << desc << std::endl;
}

void Voxey::Core::Logger::dPrint(const char* name, const char* desc, [[maybe_unused]] const std::vector<std::string>& args)
{
    std::string formattedDesc = desc;

    if (!formattedDesc.empty() && !std::isupper(formattedDesc[0]))
    {
        formattedDesc[0] = std::toupper(formattedDesc[0]);
    }

    if (!args.empty())
    {
        std::stringstream ss;
        size_t start = 0;
        size_t end = formattedDesc.find('%', start);
        size_t argIdx = 0;

        while (end != std::string::npos && argIdx < args.size())
        {
            ss << formattedDesc.substr(start, end - start);
            ss << args[argIdx++];
            start = end + 1;
            end = formattedDesc.find('%', start);
        }

        ss << formattedDesc.substr(start);
        formattedDesc = ss.str();
    }

    std::cout << name << ": " << formattedDesc << std::endl;
}
