#include "fspch.h"
#include "Renderer/Shader.h"
#include "Renderer/Renderer.h"

#include "platform/Windows/OpenGLShader.h"


namespace Farscape {


    Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None: FS_CORE_ASSERT(false, "None renderer chosen!"); return nullptr;
        case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
        case RendererAPI::API::DirectX:
        case RendererAPI::API::Metal:
        case RendererAPI::API::Vulcan:
            FS_CORE_ASSERT(false, "DirectX not implemented!"); return nullptr;
        }

        FS_CORE_ASSERT(false, "Invalid renderer API chosen!");
        return nullptr;
    }

    Ref<Shader> Shader::Create(const std::string& path)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None: FS_CORE_ASSERT(false, "None renderer chosen!"); return nullptr;
        case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(path);
        case RendererAPI::API::DirectX:
        case RendererAPI::API::Metal:
        case RendererAPI::API::Vulcan:
            FS_CORE_ASSERT(false, "DirectX not implemented!"); return nullptr;
        }

        FS_CORE_ASSERT(false, "Invalid renderer API chosen!");
        return nullptr;
    }


    void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
    {
        FS_CORE_ASSERT(!Exists(name), "Shader name already exixts");
        m_Shaders[name] = shader;
    }

    void ShaderLibrary::Add(const Ref<Shader>& shader)
    {
        auto name = shader->GetName();
        Add(name, shader);
    }

    Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& path)
    {
        auto shader = Shader::Create(path);
        Add(name, shader);
        return shader;
    }


    Ref<Shader> ShaderLibrary::Load(const std::string& path)
    {
        auto shader = Shader::Create(path);
        Add(shader);
        return shader;
    }


    Ref<Shader> ShaderLibrary::Get(const std::string& name)
    {
        FS_CORE_ASSERT(Exists(name), "Shader name does not exixt");
        return m_Shaders[name];
    }

    bool ShaderLibrary::Exists(const std::string& name) const
    {
        return m_Shaders.find(name) != m_Shaders.end();
    }

}
