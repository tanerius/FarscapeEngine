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

// Core log macros
#define FS_CORE_FATAL(...) ::Farscape::Log::GetLoggerCore()->fatal(__VA_ARGS__)
#define FS_CORE_ERROR(...) ::Farscape::Log::GetLoggerCore()->error(__VA_ARGS__)
#define FS_CORE_WARN(...)  ::Farscape::Log::GetLoggerCore()->warn(__VA_ARGS__)
#define FS_CORE_INFO(...)  ::Farscape::Log::GetLoggerCore()->info(__VA_ARGS__)
#define FS_CORE_TRACE(...) ::Farscape::Log::GetLoggerCore()->trace(__VA_ARGS__)

// Client log macros
#define FS_FATAL(...) ::Farscape::Log::GetLoggerClient()->fatal(__VA_ARGS__)
#define FS_ERROR(...) ::Farscape::Log::GetLoggerClient()->error(__VA_ARGS__)
#define FS_WARN(...)  ::Farscape::Log::GetLoggerClient()->warn(__VA_ARGS__)
#define FS_INFO(...)  ::Farscape::Log::GetLoggerClient()->info(__VA_ARGS__)
#define FS_TRACE(...) ::Farscape::Log::GetLoggerClient()->trace(__VA_ARGS__)