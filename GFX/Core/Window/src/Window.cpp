#include "GFX/Core/Window/include/Window.h"

#include "GFX/Core/Tools/include/Timer.h"
#include "spdlog/spdlog.h"

namespace GFX::Core
{
    Window::Window(int width, int height, const char* title) : _width(width), _height(height)
    {
        if (!glfwInit())
            spdlog::error("Failed to initialize GLFW");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        initWindow(title);

        glfwMakeContextCurrent(_window);
        glfwSetWindowUserPointer(_window, this);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBlendEquation(GL_FUNC_ADD);

        // WINDOW RESIZE
        glfwSetWindowSizeCallback(_window, onWindowResize);

        // KEYBOARD
        glfwSetKeyCallback(_window, onKeyboardButton);

        // MOUSE
        glfwSetScrollCallback(_window, onMouseScroll);
        glfwSetCursorPosCallback(_window, onMouseMove);
        glfwSetMouseButtonCallback(_window, onMouseButton);
    };

    void Window::runMainLoop()
    {
        Timer timer;
        while (!glfwWindowShouldClose(_window))
        {
            glfwPollEvents();

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            timer.update();

            if (_onFrameCallback)
                _onFrameCallback(timer.getDeltaTime());

            glfwSwapBuffers(_window);
        }
    }

    void Window::close() const
    {
        glfwSetWindowShouldClose(_window, GLFW_TRUE);
    }

    void Window::initWindow(const char* title)
    {
        _window = glfwCreateWindow(_width, _height, title, nullptr, nullptr);
        if (_window == nullptr)
        {
            spdlog::error("Failed to create GLFW window");
            glfwTerminate();
            return;
        }
        glfwMakeContextCurrent(_window);
        gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
    }

    void Window::onMouseMove(GLFWwindow* window, const double x, const double y)
    {
        auto* owner = static_cast<Window*>(glfwGetWindowUserPointer(window));
        if (owner)
            owner->_input.setMousePosition(x, y);
    }

    void Window::onMouseScroll(GLFWwindow* window, const double x, const double y)
    {
        auto* owner = static_cast<Window*>(glfwGetWindowUserPointer(window));
        if (owner)
            owner->_input.addScroll(x, y);
    };

    void Window::onWindowResize(GLFWwindow* window, int width, int height) {};
    void Window::onMouseButton(GLFWwindow* window, const int button, const int action, int mods)
    {
        auto* owner = static_cast<Window*>(glfwGetWindowUserPointer(window));
        if (owner)
            owner->_input.setMouseButton(button, action);
    };

    void Window::onKeyboardButton(GLFWwindow* window, const int key, int scancode, const int action,
                                  int mods)
    {
        auto* owner = static_cast<Window*>(glfwGetWindowUserPointer(window));
        if (owner)
            owner->_input.setKey(key, action);
    };

} // namespace GFX::Core
