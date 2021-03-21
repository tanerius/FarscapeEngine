#pragma once
#include "Core/Core.h"
#include "Framebuffer.h"

namespace Farscape {

    struct RenderPassSpecification
    {
        SharedRef<Framebuffer> TargetFramebuffer;
    };

    class RenderPass : public RefCounter
    {
    public:
        virtual ~RenderPass() {}

        virtual RenderPassSpecification& GetSpecification() const = 0;

        static SharedRef<RenderPass> Create(const RenderPassSpecification& spec);
    };

}