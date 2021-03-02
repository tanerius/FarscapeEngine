#pragma once
#include "Core/Codes.h"
#include <glm/glm.hpp>

namespace Farscape {
    class VertexArray;

    class RendererAPI : public IRendererAPI
    {
    public:
        enum class API {
            None = 0,
            OpenGL = 1,
            DirectX = 2,
            Metal = 3,
            Vulcan = 4
        };
    public:
        virtual ~RendererAPI() {} 
        virtual void Clear() = 0;
        virtual void SetClearColor(const glm::vec4& color) = 0;

        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

        virtual void Init() = 0;
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
        inline static API GetAPI() { return s_API;  }
    private:
        static API s_API;
    };

}
