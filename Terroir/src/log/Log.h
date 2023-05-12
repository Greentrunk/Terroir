////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Christopher J. Pohl 2023 to Present  All Rights Reserved.
//
// This file is part of TERROIR ENGINE:
// This is free software as described by the Apache 2.0 License
//
// The above copyright notice shall be included in all portions of this software
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

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
    static std::shared_ptr<spdlog::logger> sp_EngineLogger;

    static std::shared_ptr<spdlog::logger> sp_ClientLogger;
};

} // namespace Terroir

/// ---- Terroir engine logging macros ---- ///

// Engine Logging

#define TERR_ENGINE_TRACE(...) SPDLOG_LOGGER_TRACE(Terroir::Log::GetEngineLogger(), __VA_ARGS__)
#define TERR_ENGINE_DEBUG(...) SPDLOG_LOGGER_DEBUG(Terroir::Log::GetEngineLogger(), __VA_ARGS__)
#define TERR_ENGINE_INFO(...) SPDLOG_LOGGER_INFO(Terroir::Log::GetEngineLogger(), __VA_ARGS__)
#define TERR_ENGINE_WARN(...) SPDLOG_LOGGER_WARN(Terroir::Log::GetEngineLogger(), __VA_ARGS__)
#define TERR_ENGINE_ERROR(...) SPDLOG_LOGGER_ERROR(Terroir::Log::GetEngineLogger(), __VA_ARGS__)
#define TERR_ENGINE_CRITICAL(...) SPDLOG_LOGGER_CRITICAL(Terroir::Log::GetEngineLogger(), __VA_ARGS__)

// Client Logging

#define TERR_APP_TRACE(...) SPDLOG_LOGGER_TRACE(Terroir::Log::GetClientLogger(), __VA_ARGS__)
#define TERR_APP_DEBUG(...) SPDLOG_LOGGER_DEBUG(Terroir::Log::GetClientLogger(), __VA_ARGS__)
#define TERR_APP_INFO(...) SPDLOG_LOGGER_INFO(Terroir::Log::GetClientLogger(), __VA_ARGS__)
#define TERR_APP_WARN(...) SPDLOG_LOGGER_WARN(Terroir::Log::GetClientLogger(), __VA_ARGS__)
#define TERR_APP_ERROR(...) SPDLOG_LOGGER_ERROR(Terroir::Log::GetClientLogger(), __VA_ARGS__)
#define TERR_APP_CRITICAL(...) SPDLOG_LOGGER_CRITICAL(Terroir::Log::GetClientLogger(), __VA_ARGS__)

#endif // TERROIR_LOG_H
