#pragma once

#include "Renderer/RendererAPI.h"

namespace Farscape {

    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        virtual void Clear() override;
        virtual void SetClearColor(const glm::vec4& color) override;

        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
        virtual void Init() override;
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
    };

}