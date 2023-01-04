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

// Terroir engine macros
#define TERR_ENGINE_INFO(msg) SPDLOG_LOGGER_INFO(Terroir::Log::GetEngineLogger(), msg)
#define TERR_ENGINE_WARN(msg) SPDLOG_LOGGER_WARN(Terroir::Log::GetEngineLogger(), msg)
#define TERR_ENGINE_ERROR(msg) SPDLOG_LOGGER_ERROR(Terroir::Log::GetEngineLogger(), msg)
#define TERR_ENGINE_CRIT(msg) SPDLOG_LOGGER_CRITICAL(Terroir::Log::GetEngineLogger(), msg)