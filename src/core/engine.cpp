#include "engine.h"

voxey::core::Engine::Engine(GLFWwindow* window) :
    mWindow(window), 
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

    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);
    glCullFace(GL_CW);

    mTime = std::make_unique<voxey::utils::Time>();
    mRenderingEngine = std::make_unique<Rendering::Renderer>(mWindow);
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
    if (mTime != nullptr)
    {
        mTime->timeUpdate();
    }

    double deltaTime = mTime->getDeltaTime();
    timeAccu += deltaTime;

    while (timeAccu >= fixedDeltaTime)
    {
        if (mPhysicsEngine != nullptr)
        {
            mPhysicsEngine->physicsUpdate(fixedDeltaTime);
        }

        //TODO: gameLogic->update();

        timeAccu -= fixedDeltaTime;
    }

    if (mRenderingEngine != nullptr)
    {
        mRenderingEngine->renderUpdate(deltaTime);
    }

    glfwSwapBuffers(mWindow);
    glfwPollEvents();
}



