//
// Created by cjp on 1/6/23.
//

#ifndef TERROIR_GLFWWINDOW_H
#define TERROIR_GLFWWINDOW_H

#include "Tpch.h"
#include <Terroir/terroir_export.h>
#include "platform/Window.h"
#include <GLFW/glfw3.h>

namespace Terroir
{
	class TERROIR_EXPORT GLFWWindow : public WindowBaseI
	{
	public:
		GLFWWindow(const WindowProperties& props) : m_GlfwData({ props.m_Title, props.m_Width, props.m_Height })
		{
			GLFWWindow::Init();
		}

		virtual ~GLFWWindow();

		void OnUpdate() override;

		inline u32 GetWindowWidth() const override
		{
			return m_GlfwData.m_WindowWidth;
		}

		inline u32 GetWindowHeight() const override
		{
			return m_GlfwData.m_WindowHeight;
		}

		inline void SetEventCallback(const EventCallbackFn& cb) override
		{
			m_GlfwData.m_WindowCb = cb;
		}

		void SetVSync(bool) override;

		bool IsVSync() const override;

	private:
		virtual void Init();

		virtual void Shutdown();

		GLFWwindow* m_Window = nullptr;

		typedef struct GlfwData
		{
			std::string m_WindowTitle;
			u32 m_WindowWidth, m_WindowHeight;
			bool m_WindowVSync;
			EventCallbackFn m_WindowCb;

		} GlfwData;

		GlfwData m_GlfwData;
	};

}


#endif //TERROIR_GLFWWINDOW_H
