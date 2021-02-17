#include "fspch.h"
#include "Core/Log.h"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Farscape {
	std::shared_ptr<spdlog::logger> Log::m_LoggerCore;
	std::shared_ptr<spdlog::logger> Log::m_LoggerClient;
	
	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		m_LoggerCore = spdlog::stdout_color_mt("FarscapeCore");
		m_LoggerCore->set_level(spdlog::level::trace);
		m_LoggerClient = spdlog::stdout_color_mt("FarscapeClient");
		m_LoggerClient->set_level(spdlog::level::trace);
	}
}