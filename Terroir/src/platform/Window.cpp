//
// Created by cjp on 1/9/23.
//
#include "Tpch.h"
#include "Window.h"

// add platform dependent defines
#include "glfw/GLFWWindow.h"

namespace Terroir
{
	Window* Window::Create(const WindowProperties& props)
	{
		return new GLFWWindow(props);
	}
}