#include "fspch.h"
#include "WindowsInput.h"
#include "Core/Application.h"
#include "Core/Window.h"
#include <GLFW/glfw3.h>

namespace Farscape {

    Scope<Input> Input::s_Instance = CreateScope<WindowsInput>();

    bool WindowsInput::IsKeyPressedImpl(int keycode)
    {
        // get the window reference then the raw pointer
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindowReference().GetRawWindowPointer());
        int result = glfwGetKey(window, keycode);

        return result == GLFW_PRESS || result == GLFW_REPEAT;
    }

    bool WindowsInput::IsMouseButtonPressedImpl(int button)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindowReference().GetRawWindowPointer());
        int result = glfwGetMouseButton(window, button);
        return result == GLFW_PRESS;
    }

    // Must use cpp-14 or more from here on 
    std::pair<double, double> WindowsInput::GetMousePosImpl()
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindowReference().GetRawWindowPointer());
        double x, y;
        glfwGetCursorPos(window, &x, &y);

        return { x, y };
    }

    double WindowsInput::GetMousePosXImpl()
    {
        // only cpp_17 for this!
        auto[x, y] = GetMousePosImpl();
        return x;
    }

    double WindowsInput::GetMousePosYImpl()
    {
        auto[x, y] = GetMousePosImpl();
        return y;
    }
}
