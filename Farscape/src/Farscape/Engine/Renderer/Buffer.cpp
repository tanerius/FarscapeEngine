#include "fspch.h"
#include "Renderer/Renderer.h"
#include "Video/OpenGL/OpenGLBuffer.h"

namespace Farscape {

    SharedRef<VertexBuffer> VertexBuffer::Create(void* data, uint32_t size, VertexBufferUsage usage)
    {
        switch (RendererAPI::Current())
        {
        case RendererAPIType::None:    return nullptr;
        case RendererAPIType::OpenGL:  return SharedRef<OpenGLVertexBuffer>::Create(data, size, usage);
        }
        FS_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }

    SharedRef<VertexBuffer> VertexBuffer::Create(uint32_t size, VertexBufferUsage usage)
    {
        switch (RendererAPI::Current())
        {
        case RendererAPIType::None:    return nullptr;
        case RendererAPIType::OpenGL:  return SharedRef<OpenGLVertexBuffer>::Create(size, usage);
        }
        FS_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }

    SharedRef<IndexBuffer> IndexBuffer::Create(void* data, uint32_t size)
    {
        switch (RendererAPI::Current())
        {
        case RendererAPIType::None:    return nullptr;
        case RendererAPIType::OpenGL:  return SharedRef<OpenGLIndexBuffer>::Create(data, size);
        }
        FS_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;

    }

}