#include "application.h"

EntryPoint::Application::~Application()
{
	if (mWindow)
	{
		GraphicsManager::destroyWindow(mWindow);
		mWindow = nullptr;
	}
	GraphicsManager::terminateGlfw();
}

int EntryPoint::Application::run()
{
	std::cout << "running application" << std::endl;

	char buffer[256];
	if (_getcwd(buffer, sizeof(buffer)) == NULL)
	{
		std::cerr << "error getting current working directory" << std::endl;
		return EXIT_FAILURE;
	}
	else
	{
		std::cout << "current working directory: " << buffer << std::endl;
	}

	if (init() != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	if (createWindow() != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}
	mEngine = std::make_unique<Engine::Engine>(mWindow);
	return mEngine->run();
}

int EntryPoint::Application::init()
{
	return GraphicsManager::glfwInit();
}

GLFWwindow* EntryPoint::Application::getWindow()
{
	return mWindow;
}

int EntryPoint::Application::createWindow()
{
	GraphicsManager::windowHintInit();

	const auto primaryMonitor = GraphicsManager::getPrimaryMonitor();
	const auto primaryMonitorVideoMode = GraphicsManager::getVideoMode(primaryMonitor);

	const auto screenWidth = primaryMonitorVideoMode->width;
	const auto screenHeight = primaryMonitorVideoMode->height;

	const char* title = "Voxey";
	unsigned int windowWidth = 1280;
	unsigned int windowHeight = 720;

	mWindow = GraphicsManager::createWindow(windowWidth, windowHeight, title, nullptr, nullptr);
	
	if (!mWindow)
	{
		return EXIT_FAILURE;
	}

	GraphicsManager::setWindowPos(mWindow, screenWidth / 2 - windowWidth / 2, screenHeight / 2 - windowHeight / 2);
	GraphicsManager::setCurrentContext(mWindow);
	GraphicsManager::setFrameBufferCallback(mWindow, frameBufferCallback);

	mInputManager = std::make_unique<InputManager>();
	mInputManager->init(mWindow, mInputManager.get());

	GraphicsManager::gladInit();

	setupDefaultKeybinds();
	return EXIT_SUCCESS;
}

void EntryPoint::Application::frameBufferCallback(GLFWwindow* window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
}

void EntryPoint::Application::setupDefaultKeybinds()
{
	InputManager::registerKeybind(EntryPoint::Application::changeGLPolygonMode, Key::T);
	InputManager::registerKeybind([this]() { this->escapeApplication(); }, Key::ESCAPE);
}

void EntryPoint::Application::setupDebugKeybinds()
{
}

void EntryPoint::Application::changeGLPolygonMode()
{
	std::cout << "type shi" << std::endl;
	GLint currentPolygonMode[2];
	glGetIntegerv(GL_POLYGON_MODE, currentPolygonMode);

	//GLenum newMode = (currentPolygonMode[0] == GL_LINES) ? GL_FILL : GL_LINES;
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);

	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		std::cerr << "OpenGL Error: " << error << std::endl;
	}
}

void EntryPoint::Application::escapeApplication()
{
	glfwSetWindowShouldClose(getWindow(), GL_TRUE);
}
