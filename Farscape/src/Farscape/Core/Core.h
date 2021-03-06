#pragma once
#include "Versions.h"
#include <memory>

#if defined(_WIN32) // Any windows 32 or 64 bit
#if defined(_WIN64) //Windows 64bit
#define FS_PLATFORM FS_PLATFORM_WINDOWS
#if !defined(FARSCAPE_STATIC)
#if defined(FARSCAPE_BUILD_EXPORTS)
#define FARSCAPE_API __declspec(dllexport)
#else
#define FARSCAPE_API __declspec(dllimport)
#endif
#else
#define FARSCAPE_API
#endif
#else
#error "Win x86 is not supported!"
#endif
#elif defined(__APPLE__) || defined(__MACH__)
#include <TargetConditionals.h>
#define FARSCAPE_API

#if TARGET_IPHONE_SIMULATOR == 1
#define FS_PLATFORM IOS_Sim
#error "IOS simulator is not supported!"
#elif TARGET_OS_IPHONE == 1
#define FS_PLATFORM IOS
#error "IOS is not supported!"
#elif TARGET_OS_MAC == 1
#define FS_PLATFORM MacOS
// #error "MacOS is not supported!"
#else
#define HAZEL_API __declspec(dllimport)
#error "Unknown Apple platform!"
#endif
#endif

namespace Farscape {

    void InitializeEngine();
    void ShutdownEngine();

}

//#ifndef FS_PLATFORM_WINDOWS
//#error Farscape only supports Windows!
//#endif

// __VA_ARGS__ expansion to get past MSVC "bug"
#define FS_EXPAND_VARGS(x) x

#define BIT(x) (1 << x)

#define FS_BIND_EVENT_FN(fn) std::bind(&##fn, this, std::placeholders::_1)

#include "Assert.h"

#include "API/macros.h"
#include "API/types.h"
#include "Interfaces.h"

// An object interface which can lift any weight
namespace Farscape {

    template<typename T>
    using Scope = std::unique_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Scope<T> CreateScope(Args&& ... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Ref = std::shared_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args&& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    using byte = uint8_t;
}