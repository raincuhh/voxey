#include "input.h"

std::map<Key, std::function<void()>> voxey::input::Input::inputMap;

void voxey::input::Input::init(GLFWwindow* window, Input* instance)
{
	glfwSetWindowUserPointer(window, instance);
	glfwSetKeyCallback(window, windowKeyCallback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_FALSE);
}

void voxey::input::Input::registerKeybind(const std::function<void()>& callback, Key key)
{
	inputMap[key] = callback;
    std::cout << "registered keybind: " << static_cast<int>(key) << std::endl;
}

void voxey::input::Input::keyPressed(Key key)
{
    auto pressed = inputMap.find(key);

    if (pressed != inputMap.end())
    {
        std::cout << "key found: " << static_cast<int>(key) << std::endl;
        pressed->second();
    }
    else
    {
        std::cout << "key not found: " << static_cast<int>(key) << std::endl;
    }
}

void voxey::input::Input::windowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Input* instance = static_cast<Input*>(glfwGetWindowUserPointer(window));
	if (instance)
	{
		instance->handleKeyEvent(key, scancode, action, mods);
	}
	else
	{
		std::cout << "key event: " << key << ", action=" << action << std::endl;
	}
}

void voxey::input::Input::handleKeyEvent(int key, int scancode, int action, int mods)
{
    // think a better way would be to just glfw get inputkey then keypressed. i guess
	(void)scancode;

	if (action == GLFW_PRESS)
	{
		Key mappedKey = static_cast<Key>(key);
        
        switch (key)
        {
        case GLFW_KEY_ESCAPE: mappedKey = Key::ESCAPE; break;
        case GLFW_KEY_F1: mappedKey = Key::F1; break;
        case GLFW_KEY_F2: mappedKey = Key::F2; break;
        case GLFW_KEY_F3: mappedKey = Key::F3; break;
        case GLFW_KEY_F4: mappedKey = Key::F4; break;
        case GLFW_KEY_F5: mappedKey = Key::F5; break;
        case GLFW_KEY_F6: mappedKey = Key::F6; break;
        case GLFW_KEY_F7: mappedKey = Key::F7; break;
        case GLFW_KEY_F8: mappedKey = Key::F8; break;
        case GLFW_KEY_F9: mappedKey = Key::F9; break;
        case GLFW_KEY_F10: mappedKey = Key::F10; break;
        case GLFW_KEY_F11: mappedKey = Key::F11; break;
        case GLFW_KEY_F12: mappedKey = Key::F12; break;
        case GLFW_KEY_PRINT_SCREEN: mappedKey = Key::PRINT_SCREEN; break;
        case GLFW_KEY_SCROLL_LOCK: mappedKey = Key::SCROLL_LOCK; break;
        case GLFW_KEY_PAUSE: mappedKey = Key::PAUSE; break;
        case GLFW_KEY_GRAVE_ACCENT: mappedKey = Key::TILDE; break;
        case GLFW_KEY_1: mappedKey = Key::NUM_1; break;
        case GLFW_KEY_2: mappedKey = Key::NUM_2; break;
        case GLFW_KEY_3: mappedKey = Key::NUM_3; break;
        case GLFW_KEY_4: mappedKey = Key::NUM_4; break;
        case GLFW_KEY_5: mappedKey = Key::NUM_5; break;
        case GLFW_KEY_6: mappedKey = Key::NUM_6; break;
        case GLFW_KEY_7: mappedKey = Key::NUM_7; break;
        case GLFW_KEY_8: mappedKey = Key::NUM_8; break;
        case GLFW_KEY_9: mappedKey = Key::NUM_9; break;
        case GLFW_KEY_0: mappedKey = Key::NUM_0; break;
        case GLFW_KEY_MINUS: mappedKey = Key::MINUS; break;
        case GLFW_KEY_EQUAL: mappedKey = Key::EQUAL; break;
        case GLFW_KEY_BACKSPACE: mappedKey = Key::BACKSPACE; break;
        case GLFW_KEY_TAB: mappedKey = Key::TAB; break;
        case GLFW_KEY_Q: mappedKey = Key::Q; break;
        case GLFW_KEY_W: mappedKey = Key::W; break;
        case GLFW_KEY_E: mappedKey = Key::E; break;
        case GLFW_KEY_R: mappedKey = Key::R; break;
        case GLFW_KEY_T: mappedKey = Key::T; break;
        case GLFW_KEY_Y: mappedKey = Key::Y; break;
        case GLFW_KEY_U: mappedKey = Key::U; break;
        case GLFW_KEY_I: mappedKey = Key::I; break;
        case GLFW_KEY_O: mappedKey = Key::O; break;
        case GLFW_KEY_P: mappedKey = Key::P; break;
        case GLFW_KEY_LEFT_BRACKET: mappedKey = Key::LEFT_BRACKET; break;
        case GLFW_KEY_RIGHT_BRACKET: mappedKey = Key::RIGHT_BRACKET; break;
        case GLFW_KEY_ENTER: mappedKey = Key::ENTER; break;
        case GLFW_KEY_LEFT_CONTROL: mappedKey = Key::LEFT_CONTROL; break;
        case GLFW_KEY_A: mappedKey = Key::A; break;
        case GLFW_KEY_S: mappedKey = Key::S; break;
        case GLFW_KEY_D: mappedKey = Key::D; break;
        case GLFW_KEY_F: mappedKey = Key::F; break;
        case GLFW_KEY_G: mappedKey = Key::G; break;
        case GLFW_KEY_H: mappedKey = Key::H; break;
        case GLFW_KEY_J: mappedKey = Key::J; break;
        case GLFW_KEY_K: mappedKey = Key::K; break;
        case GLFW_KEY_L: mappedKey = Key::L; break;
        case GLFW_KEY_SEMICOLON: mappedKey = Key::SEMICOLON; break;
        case GLFW_KEY_APOSTROPHE: mappedKey = Key::APOSTROPHE; break;
        case GLFW_KEY_BACKSLASH: mappedKey = Key::BACKSLASH; break;
        case GLFW_KEY_Z: mappedKey = Key::Z; break;
        case GLFW_KEY_X: mappedKey = Key::X; break;
        case GLFW_KEY_C: mappedKey = Key::C; break;
        case GLFW_KEY_V: mappedKey = Key::V; break;
        case GLFW_KEY_B: mappedKey = Key::B; break;
        case GLFW_KEY_N: mappedKey = Key::N; break;
        case GLFW_KEY_M: mappedKey = Key::M; break;
        case GLFW_KEY_COMMA: mappedKey = Key::COMMA; break;
        case GLFW_KEY_PERIOD: mappedKey = Key::PERIOD; break;
        case GLFW_KEY_SLASH: mappedKey = Key::SLASH; break;
        case GLFW_KEY_RIGHT_SHIFT: mappedKey = Key::RIGHT_SHIFT; break;
        case GLFW_KEY_KP_0: mappedKey = Key::NUMPAD_0; break;
        case GLFW_KEY_KP_1: mappedKey = Key::NUMPAD_1; break;
        case GLFW_KEY_KP_2: mappedKey = Key::NUMPAD_2; break;
        case GLFW_KEY_KP_3: mappedKey = Key::NUMPAD_3; break;
        case GLFW_KEY_KP_4: mappedKey = Key::NUMPAD_4; break;
        case GLFW_KEY_KP_5: mappedKey = Key::NUMPAD_5; break;
        case GLFW_KEY_KP_6: mappedKey = Key::NUMPAD_6; break;
        case GLFW_KEY_KP_7: mappedKey = Key::NUMPAD_7; break;
        case GLFW_KEY_KP_8: mappedKey = Key::NUMPAD_8; break;
        case GLFW_KEY_KP_9: mappedKey = Key::NUMPAD_9; break;
        case GLFW_KEY_KP_DECIMAL: mappedKey = Key::NUMPAD_DECIMAL; break;
        case GLFW_KEY_KP_DIVIDE: mappedKey = Key::NUMPAD_DIVIDE; break;
        case GLFW_KEY_KP_MULTIPLY: mappedKey = Key::NUMPAD_MULTIPLY; break;
        case GLFW_KEY_KP_SUBTRACT: mappedKey = Key::NUMPAD_SUBTRACT; break;
        case GLFW_KEY_KP_ADD: mappedKey = Key::NUMPAD_ADD; break;
        case GLFW_KEY_KP_ENTER: mappedKey = Key::NUMPAD_ENTER; break;
        case GLFW_KEY_KP_EQUAL: mappedKey = Key::NUMPAD_EQUAL; break;
        case GLFW_KEY_LEFT: mappedKey = Key::LEFT_ARROW; break;
        case GLFW_KEY_UP: mappedKey = Key::UP_ARROW; break;
        case GLFW_KEY_RIGHT: mappedKey = Key::RIGHT_ARROW; break;
        case GLFW_KEY_DOWN: mappedKey = Key::DOWN_ARROW; break;
        case GLFW_KEY_INSERT: mappedKey = Key::INSERT; break;
        case GLFW_KEY_HOME: mappedKey = Key::HOME; break;
        case GLFW_KEY_PAGE_UP: mappedKey = Key::PAGE_UP; break;
        case GLFW_KEY_DELETE: mappedKey = Key::DELETE; break;
        case GLFW_KEY_END: mappedKey = Key::END; break;
        case GLFW_KEY_PAGE_DOWN: mappedKey = Key::PAGE_DOWN; break;
        case GLFW_KEY_LEFT_SUPER: mappedKey = Key::LEFT_SUPER; break;
        case GLFW_KEY_RIGHT_SUPER: mappedKey = Key::RIGHT_SUPER; break;
        case GLFW_KEY_MENU: mappedKey = Key::MENU; break;
        case GLFW_KEY_CAPS_LOCK: mappedKey = Key::CAPS_LOCK; break;
        case GLFW_KEY_NUM_LOCK: mappedKey = Key::NUM_LOCK; break;
        default: return;
        }
		keyPressed(mappedKey);
	}
}