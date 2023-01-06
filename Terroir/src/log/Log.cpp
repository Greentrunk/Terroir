//
// Created by cjp on 1/4/23.
//
#include "Log.h"

namespace Terroir
{
	// Declare statics
	std::shared_ptr<spdlog::logger> Log::sp_EngineLogger;
	std::shared_ptr<spdlog::logger> Log::sp_ClientLogger;

	// Setup spd sinks and config loggers
	void Log::Init()
	{
		auto engineSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		auto clientSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		auto pattern = "%^[%c] [%n] [%l]: %v%$";
		engineSink->set_pattern(pattern);
		engineSink->set_level(spdlog::level::trace);
		clientSink->set_pattern(pattern);
		clientSink->set_level(spdlog::level::trace);

		sp_EngineLogger = std::make_shared<spdlog::logger>("TERROIR", engineSink);
		sp_ClientLogger = std::make_shared<spdlog::logger>("APP", clientSink);
	}
} // Terroir