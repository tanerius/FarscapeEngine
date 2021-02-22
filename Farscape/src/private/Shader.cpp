#include "fspch.h"
#include "Renderer/Shader.h"
#include "Renderer/Renderer.h"

#include "Windows/OpenGLShader.h"


namespace Farscape {

    
    Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None: FS_CORE_ASSERT(false, "None renderer chosen!"); return nullptr;
            case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
            case RendererAPI::API::DirectX: 
            case RendererAPI::API::Metal: 
            case RendererAPI::API::Vulcan: 
                FS_CORE_ASSERT(false, "DirectX not implemented!"); return nullptr;
        }

        FS_CORE_ASSERT(false, "Invalid renderer API chosen!"); 
        return nullptr;
    }
    
}
