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
    std::cout << "running engine: " << mWindow << std::endl;

    glfwSwapInterval(1);
    glEnable(GL_DEPTH_TEST);


    mTime = new Time(mWindow);
    mRenderer = new Renderer(mWindow);

    double timeAcc = 0.0;
    const double fixedDeltaTime = mTime->getFixedDeltaTime();

    while (!glfwWindowShouldClose(mWindow))
    {
        mTime->update();

        //dt doesnt seem to work rn so fix this later
        double deltaTime = mTime->getDeltaTime();

        //std::cout << "delta time: " << deltaTime << std::endl;
        timeAcc += deltaTime;

        while (timeAcc >= fixedDeltaTime)
        {
            //TODO: call this from physics->update(); 
            fixedUpdate(fixedDeltaTime);
            std::cout << "fixed update, time: " << timeAcc << std::endl;

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
