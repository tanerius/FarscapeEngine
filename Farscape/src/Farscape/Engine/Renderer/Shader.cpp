#include "fspch.h"
#include "Renderer/Shader.h"
#include "Renderer/Renderer.h"

#include "Video/OpenGL/OpenGLShader.h"


namespace Farscape {


    std::vector<SharedRef<Shader>> Shader::s_AllShaders;

    SharedRef<Shader> Shader::Create(const std::string& filepath)
    {
        SharedRef<Shader> result = nullptr;

        switch (RendererAPI::Current())
        {
        case RendererAPIType::None:	    return nullptr;
        case RendererAPIType::OpenGL:   
            result = SharedRef<OpenGLShader>::Create(filepath);
            break;
        case RendererAPIType::Metal:    FS_CORE_FATAL("Metal not supported yet!"); return nullptr;
        case RendererAPIType::DirectX:  FS_CORE_FATAL("DirectX not supported yet!"); return nullptr;
        case RendererAPIType::Vulcan:   FS_CORE_FATAL("Vulcan not supported yet!"); return nullptr;
        }
        s_AllShaders.push_back(result);
        return result;
    }

    SharedRef<Shader> Shader::CreateFromString(const std::string& source)
    {
        SharedRef<Shader> result = nullptr;

        switch (RendererAPI::Current())
        {
        case RendererAPIType::None: return nullptr;
        case RendererAPIType::OpenGL: 
            result = OpenGLShader::CreateFromString(source);
            break;
        case RendererAPIType::Metal:    FS_CORE_FATAL("Metal not supported yet!"); return nullptr;
        case RendererAPIType::DirectX:  FS_CORE_FATAL("DirectX not supported yet!"); return nullptr;
        case RendererAPIType::Vulcan:   FS_CORE_FATAL("Vulcan not supported yet!"); return nullptr;
        }
        s_AllShaders.push_back(result);
        return result;
    }

    ShaderLibrary::ShaderLibrary()
    {
    }

    ShaderLibrary::~ShaderLibrary()
    {
    }

    void ShaderLibrary::Add(const SharedRef<Shader>& shader)
    {
        auto& name = shader->GetName();
        FS_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end(), "Shader not found");
        m_Shaders[name] = shader;
    }

    void ShaderLibrary::Load(const std::string& path)
    {
        auto shader = SharedRef<Shader>(Shader::Create(path));
        auto& name = shader->GetName();
        FS_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end(), "Shader not found");
        m_Shaders[name] = shader;
    }

    void ShaderLibrary::Load(const std::string& name, const std::string& path)
    {
        FS_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end(), "Shader not found");
        m_Shaders[name] = SharedRef<Shader>(Shader::Create(path));
    }

    const SharedRef<Shader>& ShaderLibrary::Get(const std::string& name) const
    {
        FS_CORE_ASSERT(m_Shaders.find(name) != m_Shaders.end(), "Shader not found");
        return m_Shaders.at(name);
    }

}
