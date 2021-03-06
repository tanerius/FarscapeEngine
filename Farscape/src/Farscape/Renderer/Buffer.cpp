#include "fspch.h"
#include "Renderer/Renderer.h"
#include "platform/Windows/OpenGLBuffer.h"

namespace Farscape {

    Ref<VertexBuffer> VertexBuffer::Create(void* data, uint32_t size, VertexBufferUsage usage)
    {
        switch (RendererAPI::Current())
        {
        case RendererAPIType::None:    return nullptr;
        case RendererAPIType::OpenGL:  return std::make_shared<OpenGLVertexBuffer>(data, size, usage);
        }
        FS_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }

    Ref<VertexBuffer> VertexBuffer::Create(uint32_t size, VertexBufferUsage usage)
    {
        switch (RendererAPI::Current())
        {
        case RendererAPIType::None:    return nullptr;
        case RendererAPIType::OpenGL:  return std::make_shared<OpenGLVertexBuffer>(size, usage);
        }
        FS_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }

    Ref<IndexBuffer> IndexBuffer::Create(void* data, uint32_t size)
    {
        switch (RendererAPI::Current())
        {
        case RendererAPIType::None:    return nullptr;
        case RendererAPIType::OpenGL:  return std::make_shared<OpenGLIndexBuffer>(data, size);
        }
        FS_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;

    }

}