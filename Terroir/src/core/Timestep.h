#ifndef TERROIR_TIMESTEP_H
#define TERROIR_TIMESTEP_H

#include "Terroir/src/core/Types.h"

namespace Terroir
{
class Timestep
{
  public:
    Timestep(f32 time = 0.0f) : m_Time(time)
    {
    }

    constexpr operator const float() const
    {
        return m_Time;
    }

    [[nodiscard]] constexpr const f32 GetSeconds() const
    {
        return m_Time;
    }

    [[nodiscard]] constexpr const f32 GetMilliseconds() const
    {
        return m_Time * 1000; // NOLINT
    }

  private:
    f32 m_Time;
};
} // namespace Terroir

#endif // !TERROIR_TIMESTEP_H
