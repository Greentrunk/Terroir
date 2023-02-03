//
// Created by cjp on 1/10/23.
//

#ifndef TERROIRBASE_INPUT_H
#define TERROIRBASE_INPUT_H

#include "Terroir/src/core/Types.h"
#include <utility>

namespace Terroir
{
class Input
{
  public:
    virtual ~Input() = default;
    static bool IsKeyPressed(i32 keycode)
    {
        return s_Instance->IsKeyPressedImpl(keycode);
    }

    static bool IsMousePressed(i32 button)
    {
        return s_Instance->IsMousePressedImpl(button);
    }

    static std::pair<f32, f32> GetMousePos()
    {
        return s_Instance->GetMousePosImpl();
    }

    static f32 GetMouseX()
    {
        return s_Instance->GetMouseXImpl();
    }

    static f32 GetMouseY()
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
    static Input *s_Instance;
};
} // namespace Terroir

#endif // TERROIRBASE_INPUT_H
