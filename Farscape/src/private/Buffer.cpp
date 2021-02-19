#include "fspch.h"
#include "Renderer/Buffer.h"
#include "Renderer/Renderer.h"
#include "Windows/OpenGLBuffer.h"

namespace Farscape {
		
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t arraySize)
	{
		// decide the API here!!!
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			{
				FS_CORE_ASSERT(false, "No renderer selected");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
			{
				return new OpenGLVertexBuffer(vertices, arraySize);
			}
		}


		FS_CORE_ASSERT(false, "Invalid renderer selected!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
			{
				FS_CORE_ASSERT(false, "No renderer selected");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
			{
				return new OpenGLIndexBuffer(indices, count);
			}
		}

		FS_CORE_ASSERT(false, "Invalid renderer selected!");
		return nullptr;
	}

}