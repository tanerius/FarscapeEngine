#include "fspch.h"
#include "FrameBuffer.h"

#include "Video/OpenGL/OpenGLFramebuffer.h"

namespace Farscape {

    SharedRef<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
    {
        SharedRef<Framebuffer> result = nullptr;

        switch (RendererAPI::Current())
        {
        case RendererAPIType::None:				return nullptr;
        case RendererAPIType::OpenGL:			
            result = SharedRef<OpenGLFramebuffer>::Create(spec);
            break;
        case RendererAPIType::Metal:			FS_CORE_FATAL("Metal not implemented yet"); return nullptr;
        case RendererAPIType::DirectX:			FS_CORE_FATAL("DirectX not implemented yet"); return nullptr;
        case RendererAPIType::Vulcan:			FS_CORE_FATAL("Vulcan not implemented yet"); return nullptr;
        }
        FramebufferPool::GetGlobal()->Add(result);
        return result;
    }

    FramebufferPool* FramebufferPool::s_Instance = new FramebufferPool;

    FramebufferPool::FramebufferPool(uint32_t /* maxFBs  = 32 */)
    {

    }

    FramebufferPool::~FramebufferPool()
    {

    }

    std::weak_ptr<Framebuffer> FramebufferPool::AllocateBuffer()
    {
        // m_Pool.push_back();
        return std::weak_ptr<Framebuffer>();
    }

    void FramebufferPool::Add(SharedRef<Framebuffer> framebuffer)
    {
        m_Pool.push_back(framebuffer);
    }

}
