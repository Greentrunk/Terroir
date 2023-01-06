//
// Created by cjp on 1/6/23.
//

#ifndef TERROIR_WINDOW_H
#define TERROIR_WINDOW_H

#include "Terroir/pch/Tpch.h"
#include <Terroir/terroir_export.h>
#include "Terroir/src/core/event/Event.h"

namespace Terroir
{
	class WindowProperties
	{
	public:
		WindowProperties(std::string windowTitle, u32 width, u32 height) : m_Title(std::move(windowTitle)),
																		   m_Width(width),
																		   m_Height(height)
		{
		}

		std::string m_Title;
		u32 m_Width;
		u32 m_Height;
	};

	// Abstract Interface for platform dependent windowing
	class TERROIR_EXPORT WindowBaseI
	{
	public:
		using EventCallbackFn = std::function<void(EventBaseI&)>;

		virtual ~WindowBaseI()
		{
		}

		virtual void OnUpdate() = 0;

		virtual u32 GetWindowWidth() const = 0;

		virtual u32 GetWindowHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn&) = 0;

		virtual void SetVSync(bool) = 0;

		virtual bool IsVSync() const = 0;

		static std::unique_ptr<WindowBaseI> Create(const WindowProperties&);
	};
}

#endif //TERROIR_WINDOW_H
