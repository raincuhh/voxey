#include "engine.h"

Engine::Engine::Engine(GLFWwindow* window) : 
    mWindow(window), 
    mTime(nullptr),
    mRenderingEngine(nullptr), 
    mPhysicsEngine(nullptr)
{
}

Engine::Engine::~Engine()
{
}

int Engine::Engine::run()
{
    GraphicsManager::bufferSwapInterval(1);
    GraphicsManager::enableDepthTest();
    GraphicsManager::setFrontFace(GL_CCW);
    GraphicsManager::setCullFace(GL_CW);

    mTime = std::make_unique<Utils::Time>();
    mRenderingEngine = std::make_unique<Rendering::Renderer>(mWindow);
    mPhysicsEngine = std::make_unique<Physics>();

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

    GraphicsManager::swapBuffers(mWindow);
    GraphicsManager::pollEvents();
}



