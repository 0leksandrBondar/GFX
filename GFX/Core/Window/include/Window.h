#pragma once

// clang-format off
#include "ExternalLibs/GLAD/include/glad/glad.h"
#include "ExternalLibs/GLFW/include/GLFW/glfw3.h"
// clang-format on

#include "GFX/Core/BaseTypes/include/NonCopyableButMovable.h"

#include <functional>

namespace GFX::Core
{
    using OnFrameCallback = std::function<void(float deltaTime)>;

    class Window final : public NonCopyableButMovable
    {
    public:
        Window(int width, int height, const char* title);

        void runMainLoop();
        void setOnFrameCallback(const OnFrameCallback& callback) { _onFrameCallback = callback; }

        static void enableDepth() { glEnable(GL_DEPTH_TEST); };

    private:
        void initWindow(const char* title);

        static void onMouseMove(GLFWwindow* window, double x, double y);
        static void onMouseScroll(GLFWwindow* window, double x, double y);
        static void onWindowResize(GLFWwindow* window, int width, int height);
        static void onMouseButton(GLFWwindow* window, int button, int action, int mods);
        static void onKeyboardButton(GLFWwindow* window, int key, int scancode, int action,
                                     int mods);

    private:
        GLFWwindow* _window{ nullptr };
        OnFrameCallback _onFrameCallback{ nullptr };

        int _width{ 0 };
        int _height{ 0 };
    };
} // namespace GFX::Core