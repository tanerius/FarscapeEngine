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
        }


        FS_CORE_ASSERT(false, "Invalid renderer selected!");
        return nullptr;
    }

}
