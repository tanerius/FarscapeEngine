#include "fspch.h"
#include "Renderer/Renderer.h"
#include "Renderer/VertexArray.h"
#include "Video/OpenGL/OpenGLVertexArray.h"

namespace Farscape {

	SharedRef<VertexArray> VertexArray::Create()
	{
		switch (RendererAPI::Current())
		{
		case RendererAPIType::None:    FS_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPIType::OpenGL:  return SharedRef<OpenGLVertexArray>::Create();
		case RendererAPIType::Metal:    FS_CORE_ASSERT(false, "RendererAPI::Metal is currently not supported!"); return nullptr;
		case RendererAPIType::DirectX:    FS_CORE_ASSERT(false, "RendererAPI::DirectX is currently not supported!"); return nullptr;
		case RendererAPIType::Vulcan:    FS_CORE_ASSERT(false, "RendererAPI::Vulcan is currently not supported!"); return nullptr;
		}

		FS_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}
