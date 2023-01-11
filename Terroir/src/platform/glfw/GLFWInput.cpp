//
// Created by cjp on 1/10/23.
//

#include "GLFWInput.h"
#include "Terroir/src/core/application/Application.h"
#include <GLFW/glfw3.h>

namespace Terroir
{
#define GET_GLFW_WINDOW_PTR static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow())

Input *Input::s_Instance{new GLFWInput()};

bool GLFWInput::IsKeyPressedImpl(i32 keycode)
{
    auto state{glfwGetKey(GET_GLFW_WINDOW_PTR, keycode)};
    auto result{state == GLFW_PRESS || state == GLFW_REPEAT};
    return result;
}

bool GLFWInput::IsMousePressedImpl(int button)
{
    auto state{glfwGetMouseButton(GET_GLFW_WINDOW_PTR, button)};
    auto result{state == GLFW_PRESS};
    return result;
}

std::pair<f32, f32> GLFWInput::GetMousePosImpl()
{
    f64 x{0.f}, y{0.f};
    glfwGetCursorPos(GET_GLFW_WINDOW_PTR, &x, &y);
    return {x, y};
}

f32 GLFWInput::GetMouseXImpl()
{
    auto [x, y]{GetMousePosImpl()};
    return x;
}

f32 GLFWInput::GetMouseYImpl()
{
    auto [x, y]{GetMousePosImpl()};
    return y;
}
} // namespace Terroir
