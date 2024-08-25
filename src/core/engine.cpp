#include "engine.h"

Engine::Engine(GLFWwindow* window) : mWindow(window), mEngine(nullptr), mTime(nullptr)
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

    mTime = new Time(mWindow);

    double lag = 0.0;
    const double fixedDeltaTime = mTime->getFixedDeltaTime();

    while (!glfwWindowShouldClose(mWindow))
    {
        mTime->update();

        double deltaTime = mTime->getDeltaTime();
        lag += deltaTime;

        while (lag >= fixedDeltaTime)
        {
            fixedUpdate(fixedDeltaTime);
            lag -= fixedDeltaTime;
        }

        update(deltaTime);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



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

void Engine::renderUpdate([[maybe_unused]] double deltaTime)
{
}
