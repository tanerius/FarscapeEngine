#pragma once
#include <glm/glm.hpp>

namespace Farscape {
    class VertexArray;

    class RendererAPI
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
        virtual void Clear() = 0;
        virtual void SetClearColor(const glm::vec4& color) = 0;

        virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

        inline static API GetAPI() { return s_API;  }
    private:
        static API s_API;
    };

}
