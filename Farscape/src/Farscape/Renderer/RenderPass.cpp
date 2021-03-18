#include "fspch.h"
#include "RenderPass.h"
#include "Renderer.h"

#include "platform/Windows/OpenGLRenderPass.h"

namespace Farscape {

    Ref<RenderPass> RenderPass::Create(const RenderPassSpecification& spec)
    {
        switch (RendererAPI::Current())
        {
        case RendererAPIType::None:         FS_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPIType::OpenGL:       return Ref<OpenGLRenderPass>::Create(spec);
        case RendererAPIType::Metal:        FS_CORE_ASSERT(false, "RendererAPI::Metal is currently not supported!"); return nullptr;
        case RendererAPIType::DirectX:      FS_CORE_ASSERT(false, "RendererAPI::DirectX is currently not supported!"); return nullptr;
        case RendererAPIType::Vulcan:       FS_CORE_ASSERT(false, "RendererAPI::Vulcan is currently not supported!"); return nullptr;
        }

        FS_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}