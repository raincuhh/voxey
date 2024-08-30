#include "engine.h"

Engine::Engine(GLFWwindow* window) : mWindow(window), mEngine(nullptr), mRenderer(nullptr), mTime(nullptr), mPhysics(nullptr)
{
}

Engine::~Engine()
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

int Engine::run()
{
    std::cout << "running engine" << std::endl;

    glfwSwapInterval(1);
    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);
    glCullFace(GL_CW);

    mTime = new Time();
    mRenderer = new Renderer(mWindow);
    mPhysics = new Physics();

    double timeAccu = 0.0;
    const double fixedDeltaTime = mTime->getFixedDeltaTime();

    while (!glfwWindowShouldClose(mWindow))
    {
        mTime->timeUpdate();
        double deltaTime = mTime->getDeltaTime();

        timeAccu += deltaTime;
        std::cout << "deltaTime: " << deltaTime << std::endl;

        while (timeAccu >= fixedDeltaTime)
        {
            mPhysics->physicsUpdate(fixedDeltaTime);
            //TODO: gameLogic->update(); gamelogic ie being whatever gamelogic shit

            timeAccu -= fixedDeltaTime;
        }

        engineUpdate(deltaTime);
        mRenderer->renderUpdate(deltaTime);

        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }
    return EXIT_SUCCESS;
}

void Engine::engineUpdate([[maybe_unused]] double deltaTime)
{
}

void Engine::fixedUpdate([[maybe_unused]] double fixedDeltaTime)
{
}
