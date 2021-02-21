#include "Renderer/Buffer.h"

namespace Farscape {

    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t arraySize);
        virtual ~OpenGLVertexBuffer() override;

        virtual void Bind() const override;
        virtual void Unbind() const override;
        virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
        virtual const BufferLayout& GetLayout() const override { return m_Layout; }
    private:
        uint32_t m_RendererID;
        BufferLayout m_Layout;
    };

    // ****************************************
    // ******** Index buffer definition below
    // ****************************************

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
        virtual ~OpenGLIndexBuffer() override;

        virtual void Bind() const override;
        virtual void Unbind() const override;

        

        virtual uint32_t GetCount() const { return m_Count;  }
    private:
        uint32_t m_RendererID;
        uint32_t m_Count;
    };

}
