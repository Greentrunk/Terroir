//
// Created by cjp on 1/10/23.
//

#ifndef TERROIRBASE_GLFWINPUT_H
#define TERROIRBASE_GLFWINPUT_H

#include "../Input.h"

namespace Terroir
{

	class GLFWInput : public Input
	{
	protected:
		bool IsKeyPressedImpl(i32) override;

		bool IsMousePressedImpl(int) override;

		std::pair<f32, f32> GetMousePosImpl() override;

		f32 GetMouseXImpl() override;

		f32 GetMouseYImpl() override;


	};

} // Terroir

#endif //TERROIRBASE_GLFWINPUT_H
