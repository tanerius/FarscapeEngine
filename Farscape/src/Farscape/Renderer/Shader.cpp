#include "fspch.h"
#include "Renderer/Shader.h"
#include "Renderer/Renderer.h"

#include "platform/Windows/OpenGLShader.h"


namespace Farscape {


    std::vector<Ref<Shader>> Shader::s_AllShaders;

    Ref<Shader> Shader::Create(const std::string& filepath)
    {
        Ref<Shader> result = nullptr;

        switch (RendererAPI::Current())
        {
        case RendererAPIType::None:	    return nullptr;
        case RendererAPIType::OpenGL:   result = std::make_shared<OpenGLShader>(filepath);
        case RendererAPIType::Metal:    FS_CORE_FATAL("Metal not supported yet!"); return nullptr;
        case RendererAPIType::DirectX:  FS_CORE_FATAL("DirectX not supported yet!"); return nullptr;
        case RendererAPIType::Vulcan:   FS_CORE_FATAL("Vulcan not supported yet!"); return nullptr;
        }
        s_AllShaders.push_back(result);
        return result;
    }

    Ref<Shader> Shader::CreateFromString(const std::string& source)
    {
        Ref<Shader> result = nullptr;

        switch (RendererAPI::Current())
        {
        case RendererAPIType::None: return nullptr;
        case RendererAPIType::OpenGL: result = OpenGLShader::CreateFromString(source);
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

    void ShaderLibrary::Add(const Ref<Shader>& shader)
    {
        auto& name = shader->GetName();
        FS_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end(), "Shader not found");
        m_Shaders[name] = shader;
    }

    void ShaderLibrary::Load(const std::string& path)
    {
        auto shader = Ref<Shader>(Shader::Create(path));
        auto& name = shader->GetName();
        FS_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end(), "Shader not found");
        m_Shaders[name] = shader;
    }

    void ShaderLibrary::Load(const std::string& name, const std::string& path)
    {
        FS_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end(), "Shader not found");
        m_Shaders[name] = Ref<Shader>(Shader::Create(path));
    }

    Ref<Shader>& ShaderLibrary::Get(const std::string& name)
    {
        FS_CORE_ASSERT(m_Shaders.find(name) != m_Shaders.end(), "Shader not found");
        return m_Shaders[name];
    }

}
