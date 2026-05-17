#pragma once

#define GLFW_INCLUDE_NONE
#include "ExternalLibs/GLFW/include/GLFW/glfw3.h"

#include <array>

namespace GFX::Core
{
    struct MouseDelta
    {
        double x{ 0.0 };
        double y{ 0.0 };
    };

    class InputHandler final
    {
    public:
        void setKey(int key, int action);
        void setMouseButton(int button, int action);
        void setMousePosition(double x, double y);
        void addScroll(double x, double y);

        [[nodiscard]] bool isKeyDown(int key) const;
        [[nodiscard]] bool isMouseButtonDown(int button) const;

        MouseDelta consumeMouseDelta();
        MouseDelta consumeScrollDelta();

        void setCursorCaptured(GLFWwindow* window, bool captured);
        [[nodiscard]] bool isCursorCaptured() const { return _cursorCaptured; }

    private:
        std::array<bool, GLFW_KEY_LAST + 1> _keys{};
        std::array<bool, GLFW_MOUSE_BUTTON_LAST + 1> _mouseButtons{};
        MouseDelta _mouseDelta{};
        MouseDelta _scrollDelta{};
        double _lastMouseX{ 0.0 };
        double _lastMouseY{ 0.0 };
        bool _hasLastMousePosition{ false };
        bool _cursorCaptured{ false };
    };
} // namespace GFX::Core
