#include "application.h"

EntryPoint::Application::~Application()
{
	if (mLogger)
	{
		delete mLogger;
		mLogger = nullptr;
	}

	if (mEngine)
	{
		delete mEngine;
		mEngine = nullptr;
	}

	if (mInputManager)
	{
		delete mInputManager;
		mInputManager = nullptr;
	}

	if (mWindow)
	{
		glfwDestroyWindow(mWindow);
		mWindow = nullptr;
	}
	glfwTerminate();
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


	mEngine = new Engine::Engine(mWindow);
	return mEngine->run();
}

int EntryPoint::Application::init()
{
	if (!WindowManager::glfwInit())
	{
		std::cout << "failed to init GLFW" << std::endl;
		return EXIT_FAILURE;
	}
	else
	{
		std::cout << "passed init GLFW" << std::endl;
	}
	return EXIT_SUCCESS;
}

GLFWwindow* EntryPoint::Application::getWindow() const
{
	return mWindow;
}

int EntryPoint::Application::createWindow()
{
	glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

	const auto primMonitor = glfwGetPrimaryMonitor();
	const auto primMonitorVideoMode = glfwGetVideoMode(primMonitor);

	const char* title = "Voxey";
	unsigned int windowWidth = 1280;
	unsigned int windowHeight = 720;

	mWindow = glfwCreateWindow(windowWidth, windowHeight, title, nullptr, nullptr);
	if (!mWindow)
	{
		std::cout << "error creating GLFW window" << std::endl;
		return EXIT_FAILURE;
	}
	else
	{
		std::cout << "created GLFW window" << std::endl;
	}

	const auto screenWidth = primMonitorVideoMode->width;
	const auto screenHeight = primMonitorVideoMode->height;

	glfwSetWindowPos(mWindow, screenWidth / 2 - windowWidth / 2, screenHeight / 2 - windowHeight / 2);

	glfwMakeContextCurrent(mWindow);
	glfwSetFramebufferSizeCallback(mWindow, frameBufferCallback);

	//mInputManager = new InputManager(mWindow);
	mInputManager = new InputManager();
	mInputManager->init(mWindow, mInputManager);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "failed to init GLAD";
		return EXIT_FAILURE;
	}
	else
	{
		std::cout << "passed init GLAD" << std::endl;
		return EXIT_SUCCESS;
	}

	setupDefaultKeybinds();
}

void EntryPoint::Application::frameBufferCallback(GLFWwindow* window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
}

void EntryPoint::Application::setupDefaultKeybinds()
{
	InputManager::registerKeybind(Application::changeGLPolygonMode, Key::T);
}

void EntryPoint::Application::setupDebugKeybinds()
{
}

void EntryPoint::Application::changeGLPolygonMode()
{
	GLint currentPolygonMode;
	glGetIntegerv(GL_FRONT_AND_BACK, &currentPolygonMode);

	if (currentPolygonMode == GL_LINES)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else if (currentPolygonMode == GL_FILL)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);
	}
}
