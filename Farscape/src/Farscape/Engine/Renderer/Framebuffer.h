#pragma once
#pragma warning(disable:4201)
#include <glm/glm.hpp>
#pragma warning(default:4201)
#include "Renderer/RendererAPI.h"

namespace Farscape {

    enum class FramebufferFormat
    {
        None = 0,
        RGBA8 = 1,
        RGBA16F = 2
    };

    struct FramebufferSpecification
    {
        uint32_t Width = 1280;
        uint32_t Height = 720;
        glm::vec4 ClearColor;
        FramebufferFormat Format;
        uint32_t Samples = 1;
        bool SwapChainTarget = false;
    };

    class Framebuffer : public RefCounter
    {
    public:
        virtual ~Framebuffer() {}
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void Resize(uint32_t width, uint32_t height, bool forceRecreate = false) = 0;

        virtual void BindTexture(uint32_t slot = 0) const = 0;

        virtual RendererID GetRendererID() const = 0;
        virtual RendererID GetColorAttachmentRendererID() const = 0;
        virtual RendererID GetDepthAttachmentRendererID() const = 0;

        virtual const FramebufferSpecification& GetSpecification() const = 0;

        static SharedRef<Framebuffer> Create(const FramebufferSpecification& spec);
    };

    class FramebufferPool final
    {
    public:
        FramebufferPool(uint32_t maxFBs = 32);
        ~FramebufferPool();

        std::weak_ptr<Framebuffer> AllocateBuffer();
        void Add(SharedRef<Framebuffer> framebuffer);

        std::vector<SharedRef<Framebuffer>>& GetAll() { return m_Pool; }
        const std::vector<SharedRef<Framebuffer>>& GetAll() const { return m_Pool; }

        inline static FramebufferPool* GetGlobal() { return s_Instance; }
    private:
        std::vector<SharedRef<Framebuffer>> m_Pool;

        static FramebufferPool* s_Instance;
    };

}
