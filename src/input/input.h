#pragma once

#include <iostream>
#include <string>
#include <set>
#include <memory>
#include <vector>
#include <functional>
#include <map>

#include "../../include/glad/glad.h"
#include "../../include/GLFW/glfw3.h"

#include "../../include/glm/glm.hpp"
#include "../../include/glm/gtc/matrix_transform.hpp"

using Key = int;
using Action = std::string;

namespace voxey::input
{
    class Input
    {
    public:
        static void init(GLFWwindow* window, Input* instance);
        static void inputUpdate();

        static void registerAction(const Action& action, Key key);
        static void unRegisterAction(const Action& action);

        static bool isActionPressed(const Action& action);
        static bool isActionJustPressed(const Action& action);
        static bool isActionJustReleased(const Action& action);
        
        static glm::vec3 getDirection();

    private:
        static std::unordered_map<Action, std::set<Key>> actionMap;
        static std::set<Key> pressedKeys;
        static std::set<Key> previousPressedKeys;

        static float lastX;
        static float lastY;
        static bool mouseMoved;
        static bool firstMouse;
        static float sensitivity;
        static float yaw;
        static float pitch;

        static glm::vec3 direction;

        static void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void glfwMouseCallback(GLFWwindow* window, double xPos, double yPos);
        static void setKeyPressed(Key key, bool pressed);
    };
}