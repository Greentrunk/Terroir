//
// Created by cjp on 1/9/23.
//

#ifndef TERROIR_WINDOW_H
#define TERROIR_WINDOW_H

#include <Terroir/terroir_export.h>
#include "Terroir/pch/Tpch.h"
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

	class TERROIR_EXPORT Window
	{
	public:

		template<typename T>
		using Scope = std::unique_ptr<T>;

		template<typename T, typename ... Args>
		constexpr Scope<T> CreateScope(Args&& ... args)
		{
			return std::make_unique<T>(std::forward<Args>(args)...);
		}

		using EventCallbackFn = std::function<void(Event&)>;

		Window() = default;

		virtual ~Window() = default;

		virtual void SetVSync(bool) = 0;

		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		virtual void OnUpdate() = 0;

		virtual inline void SetEventCallback(const EventCallbackFn& cb) = 0;

		// For other windowing systems
		static Window* Create(const WindowProperties&);
	};
}


#endif //TERROIR_WINDOW_H
