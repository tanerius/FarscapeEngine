#include "fspch.h"
#include "Core/Log.h"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Farscape {
    Ref<spdlog::logger> Log::m_LoggerCore;
    Ref<spdlog::logger> Log::m_LoggerClient;

    void Log::Init()
    {
        //("*** [%H:%M:%S %z] [thread %t] %v ***");
        //spdlog::set_pattern("*** [%H:%M:%S %z] [thread %t] %v ***");
        spdlog::set_pattern("%^[%T.%e] [%t] [%l]:[%n] [%s::%!:%#] : %v%$");
        //spdlog::set_pattern("[source %s] [function %!] [line %#] %v");
        //spdlog::set_pattern("%^[%T] %n: %v%$");
        m_LoggerCore = spdlog::stdout_color_mt("Core");
        m_LoggerCore->set_level(spdlog::level::trace);
        m_LoggerClient = spdlog::stdout_color_mt("Client");
        m_LoggerClient->set_level(spdlog::level::trace);
    }
}
