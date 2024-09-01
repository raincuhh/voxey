#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <functional>
#include <map>

#include "../../include/glad/glad.h"
#include "../../include/GLFW/glfw3.h"

enum class Key {
    ESCAPE,
    F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
    PRINT_SCREEN, SCROLL_LOCK, PAUSE,
    TILDE, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, NUM_7, NUM_8, NUM_9, NUM_0,
    MINUS, EQUAL, BACKSPACE, TAB, Q, W, E, R, T, Y, U, I, O, P,
    LEFT_BRACKET, RIGHT_BRACKET, ENTER, LEFT_CONTROL, A, S, D, F, G, H, J, K, L,
    SEMICOLON, APOSTROPHE, GRAVE_ACCENT, LEFT_SHIFT, BACKSLASH, Z, X, C, V, B, N, M,
    COMMA, PERIOD, SLASH, RIGHT_SHIFT, NUMPAD_0, NUMPAD_1, NUMPAD_2, NUMPAD_3, NUMPAD_4,
    NUMPAD_5, NUMPAD_6, NUMPAD_7, NUMPAD_8, NUMPAD_9, NUMPAD_DECIMAL, NUMPAD_DIVIDE,
    NUMPAD_MULTIPLY, NUMPAD_SUBTRACT, NUMPAD_ADD, NUMPAD_ENTER, NUMPAD_EQUAL, LEFT_ARROW,
    UP_ARROW, RIGHT_ARROW, DOWN_ARROW, INSERT, HOME, PAGE_UP, DELETE, END, PAGE_DOWN,
    LEFT_SUPER, RIGHT_SUPER, MENU, CAPS_LOCK, NUM_LOCK
};


class InputManager
{
public:
	static void init(GLFWwindow* window, InputManager* instance);
	static void registerKeybind(const std::function<void()>& callback, Key key);

private:
	static std::map<Key, std::function<void()>> inputMap;

	static void keyPressed(Key key);
	static void windowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void handleKeyEvent(int key, int scancode, int action, int mods);
};
