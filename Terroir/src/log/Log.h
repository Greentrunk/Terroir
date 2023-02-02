//
// Created by cjp on 1/4/23.
//

#ifndef TERROIR_LOG_H
#define TERROIR_LOG_H

#include <fmt/core.h> 
#include <fmt/format.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <string_view>

namespace Terroir
{
class Log
{
  public:
    constexpr static std::shared_ptr<spdlog::logger> &GetEngineLogger()
    {

        return sp_EngineLogger;
    }

    constexpr static std::shared_ptr<spdlog::logger> &GetClientLogger()
    {

        return sp_ClientLogger;
    }

    static void Init();

  private:
    static std::shared_ptr<spdlog::logger> sp_EngineLogger; // NOLINT

    static std::shared_ptr<spdlog::logger> sp_ClientLogger; // NOLINT
};

} // namespace Terroir

/// ---- Terroir engine macros ---- ///

// Engine Logging
template <typename... Args> constexpr void TERR_ENGINE_TRACE(std::string_view fmt, Args... args)
{

    Terroir::Log::GetEngineLogger()->trace(fmt::vformat(fmt, fmt::make_format_args(std::forward<Args>(args)...)));
}

template <typename... Args> constexpr void TERR_ENGINE_DEBUG(std::string_view fmt, Args... args)
{

    Terroir::Log::GetEngineLogger()->debug(fmt::vformat(fmt, fmt::make_format_args(std::forward<Args>(args)...)));
}

template <typename... Args> constexpr void TERR_ENGINE_INFO(std::string_view fmt, Args... args)
{

    Terroir::Log::GetEngineLogger()->info(fmt::vformat(fmt, fmt::make_format_args(std::forward<Args>(args)...)));
}

template <typename... Args> constexpr void TERR_ENGINE_WARN(std::string_view fmt, Args... args)
{

    Terroir::Log::GetEngineLogger()->warn(fmt::vformat(fmt, fmt::make_format_args(std::forward<Args>(args)...)));
}

template <typename... Args> constexpr void TERR_ENGINE_ERROR(std::string_view fmt, Args &&...args)
{

    Terroir::Log::GetEngineLogger()->error(fmt::vformat(fmt, fmt::make_format_args(std::forward<Args>(args)...)));
}

template <typename... Args> constexpr void TERR_ENGINE_CRIT(std::string_view fmt, Args &&...args)
{

    Terroir::Log::GetEngineLogger()->critical(fmt::vformat(fmt, fmt::make_format_args(std::forward<Args>(args)...)));
}

// Client Logging
template <typename... Args> constexpr void TERR_APP_TRACE(std::string_view fmt, Args &&...args)
{

    Terroir::Log::GetClientLogger()->trace(fmt::vformat(fmt, fmt::make_format_args(std::forward<Args>(args)...)));
}

template <typename... Args> constexpr void TERR_APP_DEBUG(std::string_view fmt, Args &&...args)
{

    Terroir::Log::GetClientLogger()->debug(fmt::vformat(fmt, fmt::make_format_args(std::forward<Args>(args)...)));
}

template <typename... Args> constexpr void TERR_APP_INFO(std::string_view fmt, Args &&...args)
{

    Terroir::Log::GetClientLogger()->info(fmt::vformat(fmt, fmt::make_format_args(std::forward<Args>(args)...)));
}

template <typename... Args> constexpr void TERR_APP_WARN(std::string_view fmt, Args &&...args)
{

    Terroir::Log::GetClientLogger()->warn(fmt::vformat(fmt, fmt::make_format_args(std::forward<Args>(args)...)));
}

template <typename... Args> constexpr void TERR_APP_ERROR(std::string_view fmt, Args &&...args)
{

    Terroir::Log::GetClientLogger()->error(fmt::vformat(fmt, fmt::make_format_args(std::forward<Args>(args)...)));
}

template <typename... Args> constexpr void TERR_APP_CRIT(std::string_view fmt, Args &&...args)
{

    Terroir::Log::GetClientLogger()->critical(fmt::vformat(fmt, fmt::make_format_args(std::forward<Args>(args)...)));
}

#endif // TERROIR_LOG_H
