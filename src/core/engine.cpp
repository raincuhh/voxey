#include "engine.h"

voxey::core::Engine::Engine(GLFWwindow* window) :
    mWindow(window),
    mFps(nullptr),
    mTime(nullptr),
    mRenderingEngine(nullptr),
    mPhysicsEngine(nullptr)
{
}

voxey::core::Engine::~Engine()
{
}

int voxey::core::Engine::run()
{
    glfwSwapInterval(1);

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEPTH_TEST);

    glFrontFace(GL_CCW);
    glCullFace(GL_CW);

    mTime = std::make_unique<voxey::utils::Time>();
    mFps = std::make_unique<voxey::debug::Fps>();
    mRenderingEngine = std::make_unique<voxey::rendering::RenderingEngine>(mWindow);
    mPhysicsEngine = std::make_unique<voxey::physics::PhysicsEngine>();

    double timeAccu = 0.0;
    const double fixedDeltaTime = mTime->getFixedDeltaTime();

    while (!glfwWindowShouldClose(mWindow))
    {
        engineUpdate(timeAccu, fixedDeltaTime);
    }
    return EXIT_SUCCESS;
}

void voxey::core::Engine::engineUpdate(double timeAccu, const double fixedDeltaTime)
{
    mTime->timeUpdate();

    double deltaTime = mTime->getDeltaTime();
    timeAccu += deltaTime;

    mFps->fpsUpdate();

    while (timeAccu >= fixedDeltaTime)
    {
        mPhysicsEngine->physicsUpdate(fixedDeltaTime);

        timeAccu -= fixedDeltaTime;
    }
    
    mRenderingEngine->renderUpdate(deltaTime);

    glfwSwapBuffers(mWindow);
    glfwPollEvents();

    if (voxey::input::Input::isActionPressed("ESC")) {
        glfwSetWindowShouldClose(mWindow, GL_TRUE);
    }
}



