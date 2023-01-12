//
// Created by cjp on 1/10/23.
//

#ifndef TERROIRBASE_INPUT_H
#define TERROIRBASE_INPUT_H

#include "Terroir/src/core/Types.h"

namespace Terroir
{
	class Input
	{
	public:
virtual ~Input() = default;
		inline static bool IsKeyPressed(i32 keycode)
		{
			return s_Instance->IsKeyPressedImpl(keycode);
		}

		inline static bool IsMousePressed(i32 button)
		{
			return s_Instance->IsMousePressedImpl(button);
		}

		inline static std::pair<f32, f32> GetMousePos()
		{
			return s_Instance->GetMousePosImpl();
		}

		inline static f32 GetMouseX()
		{
			return s_Instance->GetMouseXImpl();
		}

		inline static f32 GetMouseY()
		{
			return s_Instance->GetMouseYImpl();
		}

	protected:
		virtual bool IsKeyPressedImpl(i32) = 0;

		virtual bool IsMousePressedImpl(i32) = 0;

		virtual std::pair<f32, f32> GetMousePosImpl() = 0;

		virtual f32 GetMouseXImpl() = 0;

		virtual f32 GetMouseYImpl() = 0;

	private:
		static Input* s_Instance;

	};
}

#endif //TERROIRBASE_INPUT_H
