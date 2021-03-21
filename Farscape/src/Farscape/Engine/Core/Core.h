#pragma once
#include "Versions.h"
#include <memory>
#include "ManagedPointers.h"

#if defined(FS_WIN64) // Any windows 32 or 64 bit
    #if !defined(FARSCAPE_STATIC)
        #if defined(FARSCAPE_BUILD_EXPORTS)
            #define FARSCAPE_API __declspec(dllexport)
        #else
            #define FARSCAPE_API __declspec(dllimport)
        #endif
    #else
        #define FARSCAPE_API
    #endif
#elif defined(FS_APPLE)
    #include <TargetConditionals.h>
    #define FARSCAPE_API
#else
    #error "Unknown Apple platform!"
#endif

namespace Farscape {

    void InitializeEngine();
    void ShutdownEngine();

}

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

    using byte = uint8_t;
}