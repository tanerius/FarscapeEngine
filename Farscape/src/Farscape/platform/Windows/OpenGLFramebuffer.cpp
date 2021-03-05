#include "fspch.h"
#include "Renderer/Framebuffer.h"

#include "platform/Windows/OpenGLFramebuffer.h"

namespace Farscape {

    Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
    {
        Ref<Framebuffer> result = nullptr;

        switch (RendererAPI::Current())
        {
        case RendererAPIType::None:		return nullptr;
        case RendererAPIType::OpenGL:	result = std::make_shared<OpenGLFramebuffer>(spec);
        }
        FramebufferPool::GetGlobal()->Add(result);
        return result;
    }

    FramebufferPool* FramebufferPool::s_Instance = new FramebufferPool;

    FramebufferPool::FramebufferPool(uint32_t maxFramebuffers)
    {
        FS_ASSERT(maxFramebuffers < 32, "Max framebuffers are 32");
    }

    FramebufferPool::~FramebufferPool()
    {

    }

    std::weak_ptr<Framebuffer> FramebufferPool::AllocateBuffer()
    {
        // m_Pool.push_back();
        return std::weak_ptr<Framebuffer>();
    }

    void FramebufferPool::Add(std::weak_ptr<Framebuffer> framebuffer)
    {
        m_Pool.push_back(framebuffer);
    }

}
