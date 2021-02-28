#pragma once
#include "Versions.h"
#include <memory>

#if defined(_WIN32)
#  if !defined(FARSCAPE_STATIC)
#    if defined(FARSCAPE_BUILD_EXPORTS)
#      define FARSCAPE_API __declspec(dllexport)
#    else
#      define FARSCAPE_API __declspec(dllimport)
#    endif
#  else
#    define FARSCAPE_API
#  endif
#else // non windows
#  define FARSCAPE_API
#  define FS_PLATFORM Apple
#endif


#if defined(_WIN32)
#  define FS_PLATFORM Windows
#else // non windows
#  define FS_PLATFORM Apple
#  define FARSCAPE_API
#endif


// TODO: come up with solution for mac __debugbreak()
#if defined(FS_ENABLE_ASSERTS) && defined(_WIN32)
#define FS_ASSERT(x, ...) { if(!(x)) {FS_ERROR("Assertion failed! {0}", __VA_ARGS__); __debugbreak(); } }
#define FS_CORE_ASSERT(x, ...) { if(!(x)) {FS_CORE_ERROR("Assertion failed! {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define FS_ASSERT(x, ...) 
#define FS_CORE_ASSERT(x, ...) 
#endif

#define BIT(x) (1 << x)

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

// An object interface which can lift any weight
namespace Farscape {
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

    template<typename T>
    using Ref = std::shared_ptr<T>;
}