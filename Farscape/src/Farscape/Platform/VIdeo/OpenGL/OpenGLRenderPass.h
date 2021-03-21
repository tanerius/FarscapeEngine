#pragma once

#include "Renderer/RenderPass.h"

namespace Farscape {

    class OpenGLRenderPass : public RenderPass
    {
    public:
        OpenGLRenderPass(const RenderPassSpecification& spec);
        virtual ~OpenGLRenderPass();

        virtual RenderPassSpecification& GetSpecification() const override { return m_Specification; }
    private:
        mutable RenderPassSpecification m_Specification;
    };

}
