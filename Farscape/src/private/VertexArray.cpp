#include "fspch.h"
#include "Renderer/Renderer.h"
#include "Renderer/VertexArray.h"
#include "Windows/OpenGLVertexArray.h"

namespace Farscape {

    VertexArray* VertexArray::Create()
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
            return new OpenGLVertexArray();
        }
        case RendererAPI::API::DirectX:
        case RendererAPI::API::Metal:
        case RendererAPI::API::Vulcan:
            FS_CORE_ASSERT(false, "Not implementes API!");
            return nullptr;
        }


        FS_CORE_ASSERT(false, "Invalid renderer selected!");
        return nullptr;
    }

}
