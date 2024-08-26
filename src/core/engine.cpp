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

    mTime = new Time(mWindow);
    mRenderer = new Renderer(mWindow);

    double lag = 0.0;
    const double fixedDeltaTime = mTime->getFixedDeltaTime();

    while (!glfwWindowShouldClose(mWindow))
    {
        mTime->update();

        double deltaTime = mTime->getDeltaTime();
        lag += deltaTime;
        //std::cout << deltaTime << std::endl;
        //std::cout << "delta update, time: " << std::endl;

        while (lag >= fixedDeltaTime)
        {
            //TODO: call this from physics->update(); 
            fixedUpdate(fixedDeltaTime);
            std::cout << "fixed update, time: " << lag << std::endl;

            //TODO: call this from gameLogic->update(); gamelogic ie being whatever gamelogic shit
            lag -= fixedDeltaTime;
        }

        if (mWindow) 
        {
            update(deltaTime);
        }

        //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mRenderer->update(deltaTime);

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
