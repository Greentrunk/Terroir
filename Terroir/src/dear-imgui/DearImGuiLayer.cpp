//
// Created by cjp on 1/9/23.
//

#include "DearImGuiLayer.h"
#include "Tpch.h"
#include "core/Assert.h"
#include "core/application/Application.h"
#include "platform/glfw/DearImGuiGLFW.h"
#include "platform/glfw/GLFWWindow.h"
#include "platform/opengl/DearImGuiOpenGLRenderer.h"
#include <GLFW/glfw3.h>
#include <imgui.h>

namespace Terroir
{
DearImGuiLayer::DearImGuiLayer() : Layer("DearImGui Layer")
{
}

DearImGuiLayer::~DearImGuiLayer() = default;

void DearImGuiLayer::OnEvent(Event &event)
{
}

void DearImGuiLayer::OnDearImGuiRender()
{
#ifdef SHOW_TEST_GUI
    auto show{true};
    ImGui::ShowDemoWindow(&show);
#endif
}

void DearImGuiLayer::OnAttach()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    auto &io{ImGui::GetIO()};
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsDark();

    if (auto &style{ImGui::GetStyle()}; io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    auto glfwAddress{Application::Get().GetWindow().GetNativeWindow()};
    ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow *>(glfwAddress), true);

    // to change
    ImGui_ImplOpenGL3_Init("#version 410");
}

void DearImGuiLayer::OnDetach()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void DearImGuiLayer::Begin()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void DearImGuiLayer::End()
{
    auto &io{ImGui::GetIO()};
    auto &app{Application::Get()};
    io.DisplaySize =
        ImVec2(static_cast<f32>(app.GetWindow().GetWindowWidth()), static_cast<f32>(app.GetWindow().GetWindowHeight()));

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        auto *backupCurrentContext{glfwGetCurrentContext()};
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backupCurrentContext);
    }
}

} // namespace Terroir

// hi
