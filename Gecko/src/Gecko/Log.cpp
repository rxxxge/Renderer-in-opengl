#include "gkpch.h"
#include "Log.h"

namespace Gecko {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T][%l] %n: %v%$");

		s_CoreLogger = spdlog::stdout_color_mt("[GECKO CORE]");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("[GECKO APP]");
		s_ClientLogger->set_level(spdlog::level::trace);
	}

}