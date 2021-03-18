#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

#if !defined(SPDLOG_ACTIVE_LEVEL)
#define SPDLOG_ACTIVE_LEVEL 
#endif

namespace Farscape {
    class Log : public ILog
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
#define LOGCORE ::Farscape::Log::GetLoggerCore()
#define FS_CORE_FATAL(...) SPDLOG_LOGGER_CRITICAL(LOGCORE, __VA_ARGS__)
#define FS_CORE_ERROR(...) SPDLOG_LOGGER_ERROR(LOGCORE, __VA_ARGS__)
#define FS_CORE_WARN(...)  SPDLOG_LOGGER_WARN(LOGCORE, __VA_ARGS__) //  ::Farscape::Log::GetLoggerCore()->warn(__VA_ARGS__)
#define FS_CORE_INFO(...)  SPDLOG_LOGGER_INFO(LOGCORE, __VA_ARGS__)
#define FS_CORE_TRACE(...) SPDLOG_LOGGER_TRACE(LOGCORE, __VA_ARGS__)

// Client log macros
#define LOGCLIENT ::Farscape::Log::GetLoggerClient()
#define FS_FATAL(...) SPDLOG_LOGGER_CRITICAL(LOGCLIENT, __VA_ARGS__)
#define FS_ERROR(...) SPDLOG_LOGGER_ERROR(LOGCLIENT, __VA_ARGS__)
#define FS_WARN(...)  SPDLOG_LOGGER_WARN(LOGCLIENT, __VA_ARGS__) // ::Farscape::Log::GetLoggerClient()->warn(__VA_ARGS__)
#define FS_INFO(...)  SPDLOG_LOGGER_INFO(LOGCLIENT, __VA_ARGS__)
#define FS_TRACE(...) SPDLOG_LOGGER_TRACE(LOGCLIENT, __VA_ARGS__)
