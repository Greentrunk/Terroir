//
// Created by cjp on 1/4/23.
//

#ifndef TERROIR_LOG_H
#define TERROIR_LOG_H

#include <memory>
#include <Terroir/terroir_export.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Terroir
{

	class TERROIR_EXPORT Log
	{
	public:

		inline static std::shared_ptr <spdlog::logger>& GetEngineLogger()
		{
			return sp_EngineLogger;
		}

		inline static std::shared_ptr <spdlog::logger>& GetClientLogger()
		{
			return sp_ClientLogger;
		}

		static void Init();

	private:
		static std::shared_ptr <spdlog::logger> sp_EngineLogger;

		static std::shared_ptr <spdlog::logger> sp_ClientLogger;
	};

} // Terroir

#endif //TERROIR_LOG_H

/// ---- Terroir engine macros ---- ///

// Engine Logging
#define TERR_ENGINE_INFO(...) SPDLOG_LOGGER_INFO(Terroir::Log::GetEngineLogger(), __VA_ARGS__)
#define TERR_ENGINE_WARN(...) SPDLOG_LOGGER_WARN(Terroir::Log::GetEngineLogger(), __VA_ARGS__)
#define TERR_ENGINE_ERROR(...) SPDLOG_LOGGER_ERROR(Terroir::Log::GetEngineLogger(), __VA_ARGS__)
#define TERR_ENGINE_CRIT(...) SPDLOG_LOGGER_CRITICAL(Terroir::Log::GetEngineLogger(), __VA_ARGS__)

// Client Logging
#define TERR_APP_INFO(...) SPDLOG_LOGGER_INFO(Terroir::Log::GetClientLogger(), __VA_ARGS__)
#define TERR_APP_WARN(...) SPDLOG_LOGGER_WARN(Terroir::Log::GetClientLogger(), __VA_ARGS__)
#define TERR_APP_ERROR(...) SPDLOG_LOGGER_ERROR(Terroir::Log::GetClientLogger(), __VA_ARGS__)
#define TERR_APP_CRIT(...) SPDLOG_LOGGER_CRITICAL(Terroir::Log::GetClientLogger(), __VA_ARGS__)