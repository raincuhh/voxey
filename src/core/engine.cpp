#include "engine.h"

Engine::Engine::Engine(GLFWwindow* window) : mWindow(window), mEngine(nullptr), mRenderer(nullptr), mTime(nullptr), mPhysics(nullptr)
{
}

Engine::Engine::~Engine()
{
    if (mRenderer)
    {
        delete mRenderer;
        mRenderer = nullptr;
    }

    if (mPhysics)
    {
        delete mPhysics;
        mPhysics = nullptr;
    }

    if (mTime)
    {
        delete mTime;
        mTime = nullptr;
    }
}

int Engine::Engine::run()
{
    glfwSwapInterval(1);
    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);
    glCullFace(GL_CW);

    mTime = new Utils::Time();
    mRenderer = new Rendering::Renderer(mWindow);
    mPhysics = new Physics();

    double timeAccu = 0.0;
    const double fixedDeltaTime = mTime->getFixedDeltaTime();

    while (!glfwWindowShouldClose(mWindow))
    {
        engineUpdate(timeAccu, fixedDeltaTime);
    }
    return EXIT_SUCCESS;
}

void Engine::Engine::engineUpdate(double timeAccu, const double fixedDeltaTime)
{
    if (mTime != nullptr)
    {
        mTime->timeUpdate();
    }

    double deltaTime = mTime->getDeltaTime();
    timeAccu += deltaTime;

    while (timeAccu >= fixedDeltaTime)
    {
        if (mPhysics != nullptr)
        {
            mPhysics->physicsUpdate(fixedDeltaTime);
        }

        //TODO: gameLogic->update();

        timeAccu -= fixedDeltaTime;
    }

    if (mRenderer != nullptr)
    {
        mRenderer->renderUpdate(deltaTime);
    }

    glfwSwapBuffers(mWindow);
    glfwPollEvents();
}



