#pragma once

#include "Renderer/RenderPass.h"

namespace Farscape {

    class OpenGLRenderPass : public RenderPass
    {
    public:
        OpenGLRenderPass(const RenderPassSpecification& spec);
        virtual ~OpenGLRenderPass();

        virtual RenderPassSpecification& GetSpecification() override { return m_Specification; }
    private:
        RenderPassSpecification m_Specification;
    };

}
