#pragma once
#include "Core/Codes.h"
#include <glm/glm.hpp>

namespace Farscape {

   
    class VertexArray;

    enum class RendererAPIType
    {
        None = 0,
        OpenGL = 1,
        DirectX = 2,
        Metal = 3,
        Vulcan = 4
    };

    struct RenderAPICapabilities
    {
        std::string Vendor;
        std::string Renderer;
        std::string Version;

        int MaxSamples = 0;
        float MaxAnisotropy = 0.0f;
        int MaxTextureUnits = 0;
    };

    class RendererAPI : public IRendererAPI
    {
    private:

    public:
        static void Init();
        static void Shutdown();

        static void Clear(float r, float g, float b, float a);
        static void SetClearColor(float r, float g, float b, float a);

        static void DrawIndexed(uint32_t count, PrimitiveType type, bool depthTest = true);
        static void SetLineThickness(float thickness);

        static RenderAPICapabilities& GetCapabilities()
        {
            static RenderAPICapabilities capabilities;
            return capabilities;
        }

        static RendererAPIType Current() { return s_CurrentRendererAPI; }
    private:
        static void LoadRequiredAssets();
    private:
        static RendererAPIType s_CurrentRendererAPI;
    };


}
