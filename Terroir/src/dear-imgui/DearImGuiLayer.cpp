//
// Created by cjp on 1/9/23.
//

#include "DearImGuiLayer.h"
#include "Tpch.h"
#include "platform/opengl/DearImGuiOpenGLRenderer.h"
#include "platform/glfw/DearImGuiGLFW.h"
#include "core/application/Application.h"
#include "platform/glfw/GLFWWindow.h"

namespace Terroir
{
	DearImGuiLayer::DearImGuiLayer() : Layer("DearImGui Layer")
	{
	}

	DearImGuiLayer::~DearImGuiLayer()
	{

	}

	void DearImGuiLayer::OnUpdate()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// maybe delta time?

#ifdef SHOW_TEST_GUI
		bool show = true;
		ImGui::ShowDemoWindow(&show);
#endif

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void DearImGuiLayer::OnEvent(Event& event)
	{
	}

	void DearImGuiLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		auto& glfwAddress = Application::Get().GetWindow();
		ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(glfwAddress.GetNativeWindow()), true);

		// to change
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void DearImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
} // Terroir