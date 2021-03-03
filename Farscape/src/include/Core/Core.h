#pragma once
#include "Versions.h"
#include <memory>

#if defined(_WIN32) // Any windows 32 or 64 bit
    #if defined(_WIN64) //Windows 64bit
        #define FS_PLATFORM Windows
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

#if defined(FS_ENABLE_ASSERTS)
    #if defined(_WIN64)
        #define FS_ASSERT(x, ...) { if(!(x)) {FS_ERROR("Assertion failed! {0}", __VA_ARGS__); __debugbreak(); } }
        #define FS_CORE_ASSERT(x, ...) { if(!(x)) {FS_CORE_ERROR("Assertion failed! {0}", __VA_ARGS__); __debugbreak(); } }
    #elif FS_PLATFORM == MacOS
        #define FS_ASSERT(x, ...) //{ if(!(x)) {FS_ERROR("Assertion failed! {0}", __VA_ARGS__); __asm__("int $3"); } }
        #define FS_CORE_ASSERT(x, ...) //{FS_CORE_ERROR("Assertion failed! {0}", __VA_ARGS__); __asm__("int $3"); } }
    #endif
#endif

#define BIT(x) (1 << x)

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

// An object interface which can lift any weight
namespace Farscape {

    void Initialize();
    
    void Shutdown();

    class FARSCAPE_API IFarscapeObject
    {

    };

    class FARSCAPE_API IRendererObject : public IFarscapeObject
    {

    };

    class FARSCAPE_API ICoreObject : public IFarscapeObject
    {

    };

    class FARSCAPE_API ITypeObject : public IFarscapeObject
    {

    };

    class FARSCAPE_API ICollection : public IFarscapeObject
    {

    };

    class FARSCAPE_API IController : public IFarscapeObject
    {

    };

    // #################################################################

    class FARSCAPE_API IType : public ITypeObject
    {

    };

    class FARSCAPE_API IApplication : public ICoreObject
    {

    };

    class FARSCAPE_API ITimestep : public ICoreObject
    {

    };

    class FARSCAPE_API ILayer : public ICoreObject
    {

    };

    class FARSCAPE_API IInput : public ICoreObject
    {

    };

    class FARSCAPE_API ILayerstack : public ICoreObject
    {

    };

    class FARSCAPE_API IWindow : public ICoreObject
    {

    };

    class FARSCAPE_API IEvent : public ICoreObject
    {

    };

    class FARSCAPE_API ILog : public ICoreObject
    {

    };

    class FARSCAPE_API ICommand : public ICoreObject
    {

    };


    class FARSCAPE_API IRenderCommand : public ICommand
    {

    };

    class FARSCAPE_API IRenderCommandQueue : public ICoreObject
    {

    };

    // #################################################################

    class FARSCAPE_API IShader : public IRendererObject
    {

    };

    class FARSCAPE_API IContext : public IRendererObject
    {

    };

    class FARSCAPE_API ICamera : public IRendererObject
    {

    };

    class FARSCAPE_API IBuffer : public IRendererObject
    {

    };

    class FARSCAPE_API IRenderer : public IRendererObject
    {

    };

    class FARSCAPE_API IRendererAPI : public IRendererObject
    {

    };

    class FARSCAPE_API IVertexArray : public IRendererObject
    {

    };

    class FARSCAPE_API IBufferLayout : public IRendererObject
    {

    };

    class FARSCAPE_API ITexture : public IRendererObject
    {

    };

    // #################################################################

    class FARSCAPE_API ICameraController : public IController
    {
    public:
        virtual const ICamera* GetCameraInterface() = 0;
    };



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
}