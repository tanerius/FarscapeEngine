#include "fspch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Farscape {

    static GLenum ShaderDataTypeToOpenGLType(ShaderDataType type)
    {
        switch (type)
        {
        case ShaderDataType::Float:        return GL_FLOAT;
        case ShaderDataType::Float2:    return GL_FLOAT;
        case ShaderDataType::Float3:    return GL_FLOAT;
        case ShaderDataType::Float4:    return GL_FLOAT;
        case ShaderDataType::Mat3:        return GL_FLOAT;
        case ShaderDataType::Mat4:        return GL_FLOAT;
        case ShaderDataType::Int:        return GL_INT;
        case ShaderDataType::Int2:        return GL_INT;
        case ShaderDataType::Int3:        return GL_INT;
        case ShaderDataType::Int4:        return GL_INT;
        case ShaderDataType::Bool:        return GL_BOOL;
        }

        FS_CORE_ASSERT(false, "Unknown ShaderDataTypeToOpenGLType!");
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray()
    {
        glGenVertexArrays(1, &m_RendererID);
        glBindVertexArray(m_RendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_RendererID);
    }

    void OpenGLVertexArray::Unbind() const 
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
    {
        FS_CORE_ASSERT(vertexBuffer->GetLayout().GetEmelents().size(), "Adding vertex buffer with empty layout!");

        glBindVertexArray(m_RendererID);
        vertexBuffer->Bind();

        uint32_t index = 0;
        const auto& layout = vertexBuffer->GetLayout();

        for (const auto& e : layout)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(
                index,
                e.GetComponentCount(),
                ShaderDataTypeToOpenGLType(e.type),
                e.normalized ? GL_TRUE : GL_FALSE,
                layout.GetStride(),
                (const void*)((uint64_t)e.offset));
            index++;
        }
        m_VertexBufferRefList.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
    {
        glBindVertexArray(m_RendererID);
        indexBuffer->Bind();

        m_IndexBufferRef = indexBuffer;
    }

}
