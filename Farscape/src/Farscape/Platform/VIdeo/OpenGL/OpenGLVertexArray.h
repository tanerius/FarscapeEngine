#pragma once 
#include "Renderer/VertexArray.h"

namespace Farscape {

    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void AddVertexBuffer(const SharedRef<VertexBuffer>& vertexBuffer) override;
        virtual void SetIndexBuffer(const SharedRef<IndexBuffer>& indexBuffer) override;

        virtual const std::vector<SharedRef<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }
        virtual const SharedRef<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }

        virtual RendererID GetRendererID() const override { return m_RendererID; };
    private:
        RendererID m_RendererID = 0;
        uint32_t m_VertexBufferIndex = 0;
        std::vector<SharedRef<VertexBuffer>> m_VertexBuffers;
        SharedRef<IndexBuffer> m_IndexBuffer;
    };

}
