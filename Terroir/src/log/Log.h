//
// Created by cjp on 1/4/23.
//

#ifndef TERROIR_LOG_H
#define TERROIR_LOG_H

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace Terroir
{
class Log
{
  public:
    inline static std::shared_ptr<spdlog::logger> &GetEngineLogger()
    {

        return sp_EngineLogger;
    }

    inline static std::shared_ptr<spdlog::logger> &GetClientLogger()
    {

        return sp_ClientLogger;
    }

    static void Init();

  private:
    static std::shared_ptr<spdlog::logger> sp_EngineLogger;

    static std::shared_ptr<spdlog::logger> sp_ClientLogger;
};

} // namespace Terroir

/// ---- Terroir engine macros ---- ///

// Engine Logging
template <typename... Args> constexpr void TERR_ENGINE_TRACE(fmt::format_string<Args...> args)
{
    Terroir::Log::GetEngineLogger()->trace(args);
}

template <typename... Args> constexpr void TERR_ENGINE_DEBUG(Args... args)
{
    Terroir::Log::GetEngineLogger()->debug(args...);
}

template <typename... Args> constexpr void TERR_ENGINE_INFO(Args... args)
{

    Terroir::Log::GetEngineLogger()->info(args...);
}
template <typename... Args> constexpr void TERR_ENGINE_WARN(Args... args)
{

    Terroir::Log::GetEngineLogger()->warn(args...);
}
template <typename... Args> constexpr void TERR_ENGINE_ERROR(Args... args)
{

    Terroir::Log::GetEngineLogger()->error(args...);
}
template <typename... Args> constexpr void TERR_ENGINE_CRIT(Args... args)
{

    Terroir::Log::GetEngineLogger()->critical(args...);
}

// Client Logging

template <typename... Args> constexpr void TERR_APP_TRACE(Args... args)
{
    Terroir::Log::GetClientLogger()->trace(args...);
}

template <typename... Args> constexpr void TERR_APP_DEBUG(Args... args)
{
    Terroir::Log::GetClientLogger()->debug(args...);
}

template <typename... Args> constexpr void TERR_APP_INFO(Args... args)
{
    Terroir::Log::GetClientLogger()->info(args...);
}

template <typename... Args> constexpr void TERR_APP_WARN(Args... args)
{
    Terroir::Log::GetClientLogger()->warn(args...);
}

template <typename... Args> constexpr void TERR_APP_ERROR(Args... args)
{
    Terroir::Log::GetClientLogger()->error(args...);
}

template <typename... Args> constexpr void TERR_APP_CRIT(Args... args)
{
    Terroir::Log::GetClientLogger()->critical(args...);
}

#endif // TERROIR_LOG_H
