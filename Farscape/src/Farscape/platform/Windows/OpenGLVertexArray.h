#pragma once 
#include <memory>
#include "Renderer/VertexArray.h"

namespace Farscape {

    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray();
        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
        virtual void SetIndexBuffer(const Ref<IndexBuffer>& IndexBuffer) override;

        virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override
        {
            return m_VertexBufferRefList;
        }

        virtual const Ref<IndexBuffer>& GetIndexBuffer() const override
        {
            return m_IndexBufferRef;
        }

        
    private:
        std::vector<Ref<VertexBuffer>> m_VertexBufferRefList;
        Ref<IndexBuffer> m_IndexBufferRef;
        uint32_t m_RendererID;
        uint32_t m_VertexBufferIndex = 0;
    };

}
