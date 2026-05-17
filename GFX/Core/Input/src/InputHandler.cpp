#include "GFX/Core/Input/include/InputHandler.h"

namespace GFX::Core
{
    void InputHandler::setKey(const int key, const int action)
    {
        if (key < 0 || key >= static_cast<int>(_keys.size()))
            return;

        if (action == GLFW_PRESS)
            _keys[key] = true;
        else if (action == GLFW_RELEASE)
            _keys[key] = false;
    }

    void InputHandler::setMouseButton(const int button, const int action)
    {
        if (button < 0 || button >= static_cast<int>(_mouseButtons.size()))
            return;

        if (action == GLFW_PRESS)
            _mouseButtons[button] = true;
        else if (action == GLFW_RELEASE)
            _mouseButtons[button] = false;
    }

    void InputHandler::setMousePosition(const double x, const double y)
    {
        if (!_hasLastMousePosition)
        {
            _lastMouseX = x;
            _lastMouseY = y;
            _hasLastMousePosition = true;
            return;
        }

        _mouseDelta.x += x - _lastMouseX;
        _mouseDelta.y += _lastMouseY - y;
        _lastMouseX = x;
        _lastMouseY = y;
    }

    void InputHandler::addScroll(const double x, const double y)
    {
        _scrollDelta.x += x;
        _scrollDelta.y += y;
    }

    bool InputHandler::isKeyDown(const int key) const
    {
        if (key < 0 || key >= static_cast<int>(_keys.size()))
            return false;

        return _keys[key];
    }

    bool InputHandler::isMouseButtonDown(const int button) const
    {
        if (button < 0 || button >= static_cast<int>(_mouseButtons.size()))
            return false;

        return _mouseButtons[button];
    }

    MouseDelta InputHandler::consumeMouseDelta()
    {
        const MouseDelta delta = _mouseDelta;
        _mouseDelta = {};
        return delta;
    }

    MouseDelta InputHandler::consumeScrollDelta()
    {
        const MouseDelta delta = _scrollDelta;
        _scrollDelta = {};
        return delta;
    }

    void InputHandler::setCursorCaptured(GLFWwindow* window, const bool captured)
    {
        if (!window)
            return;

        _cursorCaptured = captured;
        _hasLastMousePosition = false;
        glfwSetInputMode(window, GLFW_CURSOR, captured ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
    }
} // namespace GFX::Core
