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

    private:
        static std::unordered_map<Action, std::set<Key>> actionMap;
        static std::set<Key> pressedKeys;
        static std::set<Key> previousPressedKeys;

        static void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void setKeyPressed(Key key, bool pressed);
    };
}




