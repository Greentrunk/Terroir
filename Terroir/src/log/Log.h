//
// Created by cjp on 1/4/23.
//

#ifndef TERROIR_LOG_H
#define TERROIR_LOG_H

#include <Terroir/terroir_export.h>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Terroir
{

	class TERROIR_EXPORT Log
	{
	public:
		inline static std::shared_ptr<spdlog::logger>& GetEngineLogger()
		{

			return sp_EngineLogger;
		}

		inline static std::shared_ptr<spdlog::logger>& GetClientLogger()
		{

			return sp_ClientLogger;
		}

		static void Init();

	private:
		static std::shared_ptr<spdlog::logger> sp_EngineLogger;

		static std::shared_ptr<spdlog::logger> sp_ClientLogger;
	};

} // Terroir

#endif //TERROIR_LOG_H

/// ---- Terroir engine macros ---- ///

// Engine Logging
#define TERR_ENGINE_TRACE(...) Terroir::Log::GetEngineLogger()->trace(__VA_ARGS__)
#define TERR_ENGINE_DEBUG(...) Terroir::Log::GetEngineLogger()->debug(__VA_ARGS__)
#define TERR_ENGINE_INFO(...) Terroir::Log::GetEngineLogger()->info(__VA_ARGS__)
#define TERR_ENGINE_WARN(...) Terroir::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define TERR_ENGINE_ERROR(...) Terroir::Log::GetEngineLogger()->error(__VA_ARGS__)
#define TERR_ENGINE_CRIT(...) Terroir::Log::GetEngineLogger()->critical(__VA_ARGS__)

// Client Logging
#define TERR_APP_TRACE(...) Terroir::Log::GetClientLogger()->trace(__VA_ARGS__)
#define TERR_APP_DEBUG(...) Terroir::Log::GetClientLogger()->debug(__VA_ARGS__)
#define TERR_APP_INFO(...) Terroir::Log::GetClientLogger()->info(__VA_ARGS__)
#define TERR_APP_WARN(...) Terroir::Log::GetClientLogger()->warn(__VA_ARGS__)
#define TERR_APP_ERROR(...) Terroir::Log::GetClientLogger()->error(__VA_ARGS__)
#define TERR_APP_CRIT(...) Terroir::Log::GetClientLogger()->critical(__VA_ARGS__)