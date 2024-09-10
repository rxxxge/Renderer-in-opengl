#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Gecko {

	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// CORE MACROS
#define GK_CORE_TRACE(...)		::Gecko::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define GK_CORE_INFO(...)		::Gecko::Log::GetCoreLogger()->info(__VA_ARGS__)
#define GK_CORE_WARN(...)		::Gecko::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define GK_CORE_ERROR(...)		::Gecko::Log::GetCoreLogger()->error(__VA_ARGS__)
#define GK_CORE_FATAL(...)		::Gecko::Log::GetCoreLogger()->critical(__VA_ARGS__)

// CLIENT MACROS
#define GK_TRACE(...)			::Gecko::Log::GetClientLogger()->trace(__VA_ARGS__)
#define GK_INFO(...)			::Gecko::Log::GetClientLogger()->info(__VA_ARGS__)
#define GK_WARN(...)			::Gecko::Log::GetClientLogger()->warn(__VA_ARGS__)
#define GK_ERROR(...)			::Gecko::Log::GetClientLogger()->error(__VA_ARGS__)
#define GK_FATAL(...)			::Gecko::Log::GetClientLogger()->critical(__VA_ARGS__)