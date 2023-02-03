//
// Created by cjp on 1/9/23.
//
#include "Window.h"
#include "Tpch.h"

// add platform dependent defines
#include "glfw/GLFWWindow.h"

namespace Terroir
{
std::unique_ptr<Window> Window::Create(const WindowProperties &props)
{
    return std::make_unique<GLFWWindow>(props);
}
} // namespace Terroir