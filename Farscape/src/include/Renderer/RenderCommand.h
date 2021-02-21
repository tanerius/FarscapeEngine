#pragma once

#include "RendererAPI.h"


namespace Farscape {

    class RenderCommand : public IRenderCommand
    {
    public:
        inline static void Clear() 
        {
            s_RendererAPI->Clear();
        }

        inline static void SetClearColor(const glm::vec4& color) 
        {
            s_RendererAPI->SetClearColor(color);
        }

        inline static void DrawIndexed(const Ref<VertexArray>& vertexArr)
        {
            s_RendererAPI->DrawIndexed(vertexArr);
        }
    private:
        static RendererAPI* s_RendererAPI;
    };

}
