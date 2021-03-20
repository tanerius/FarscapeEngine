#pragma once 

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

    class FARSCAPE_API IMesh : public IRendererObject
    {

    };

}
