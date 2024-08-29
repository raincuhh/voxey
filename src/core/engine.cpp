#include "engine.h"

Engine::Engine(GLFWwindow* window) : mWindow(window), mEngine(nullptr), mRenderer(nullptr), mTime(nullptr)
{
}

Engine::~Engine()
{
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


    mTime = new Time(mWindow);
    mRenderer = new Renderer(mWindow);

    double timeAcc = 0.0;
    const double fixedDeltaTime = mTime->getFixedDeltaTime();

    while (!glfwWindowShouldClose(mWindow))
    {
        mTime->timeUpdate();
        double deltaTime = mTime->getDeltaTime();

        timeAcc += deltaTime;
        std::cout << "deltaTime: " << deltaTime << std::endl;

        while (timeAcc >= fixedDeltaTime)
        {
            //TODO: call this from physics->update(); 
            fixedUpdate(fixedDeltaTime);

            //TODO: call this from gameLogic->update(); gamelogic ie being whatever gamelogic shit
            timeAcc -= fixedDeltaTime;
        }

        update(deltaTime);
        mRenderer->renderUpdate(deltaTime);

        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }

    return EXIT_SUCCESS;
}

void Engine::update([[maybe_unused]] double deltaTime)
{
}

void Engine::fixedUpdate([[maybe_unused]] double fixedDeltaTime)
{
}
