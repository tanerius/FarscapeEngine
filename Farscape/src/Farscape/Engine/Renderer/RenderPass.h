#pragma once
#include "Core/Core.h"
#include "Framebuffer.h"

namespace Farscape {

    struct RenderPassSpecification
    {
        Ref<Framebuffer> TargetFramebuffer;
    };

    class RenderPass
    {
    public:
        virtual ~RenderPass() {}

        virtual const RenderPassSpecification& GetSpecification() const = 0;

        static Ref<RenderPass> Create(const RenderPassSpecification& spec);
    };

}