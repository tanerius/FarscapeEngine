#include "fspch.h"
#include "Renderer/Texture.h"
#include "Renderer/Renderer.h"

#include "platform/Windows/OpenGLTexture.h"

namespace Farscape {

    Ref<Texture2D> Texture2D::Create(const std::string& path)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:    FS_CORE_ASSERT(false, "RendererAPI::None not supported!"); return nullptr;
        case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLTexture2D>(path);
        case RendererAPI::API::DirectX:
        case RendererAPI::API::Metal:
        case RendererAPI::API::Vulcan:  FS_CORE_ASSERT(false, "RendererAPI::None implemented!"); return nullptr;
        }

        FS_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}
