#pragma once
#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"


namespace Farscape {
	class FARSCAPE_API Log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetLoggerCore() { return m_LoggerCore; }
		inline static std::shared_ptr<spdlog::logger>& GetLoggerClient() { return m_LoggerClient; }
	private:
		static std::shared_ptr<spdlog::logger> m_LoggerCore;
		static std::shared_ptr<spdlog::logger> m_LoggerClient;
	};
}