#pragma once

#include "Core/Core.h"

#include "Renderer/Shader.h"
#include "Renderer/Texture.h"

#include <unordered_set>

namespace Farscape {

    enum class MaterialFlag
    {
        None = BIT(0),
        DepthTest = BIT(1),
        Blend = BIT(2)
    };

    class Material : public IRendererObject, public RefCounter
    {
        friend class MaterialInstance;
    public:
        Material(const SharedRef<Shader>& shader);
        virtual ~Material();

        void Bind();

        uint32_t GetFlags() const { return m_MaterialFlags; }
        void SetFlag(MaterialFlag flag) { m_MaterialFlags |= (uint32_t)flag; }

        template <typename T>
        void Set(const std::string& name, const T& value)
        {
            auto decl = FindUniformDeclaration(name);

            FS_CORE_ASSERT(decl, "Could not find uniform with name 'x'");
            auto& buffer = GetUniformBufferTarget(decl);
            buffer.Write((byte*)&value, decl->GetSize(), decl->GetOffset());

            for (auto mi : m_MaterialInstances)
                mi->OnMaterialValueUpdated(decl);
        }

        void Set(const std::string& name, const SharedRef<Texture>& texture)
        {
            auto decl = FindResourceDeclaration(name);
            uint32_t slot = decl->GetRegister();
            if (m_Textures.size() <= slot)
                m_Textures.resize((size_t)slot + 1);
            m_Textures[slot] = texture;
        }

        void Set(const std::string& name, const SharedRef<Texture2D>& texture)
        {
            Set(name, (const SharedRef<Texture>&)texture);
        }

        void Set(const std::string& name, const SharedRef<TextureCube>& texture)
        {
            Set(name, (const SharedRef<Texture>&)texture);
        }
    public:
        static SharedRef<Material> Create(const SharedRef<Shader>& shader);
    private:
        void AllocateStorage();
        void OnShaderReloaded();
        void BindTextures() const;

        ShaderUniformDeclaration* FindUniformDeclaration(const std::string& name);
        ShaderResourceDeclaration* FindResourceDeclaration(const std::string& name);
        Buffer& GetUniformBufferTarget(ShaderUniformDeclaration* uniformDeclaration);
    private:
        SharedRef<Shader> m_Shader;
        std::unordered_set<MaterialInstance*> m_MaterialInstances;

        Buffer m_VSUniformStorageBuffer;
        Buffer m_PSUniformStorageBuffer;
        std::vector<SharedRef<Texture>> m_Textures;

        uint32_t m_MaterialFlags;
    };

    class MaterialInstance :  public RefCounter
    {
        friend class Material;
    public:
        MaterialInstance(const SharedRef<Material>& material);
        virtual ~MaterialInstance();

        template <typename T>
        void Set(const std::string& name, const T& value)
        {
            auto decl = m_Material->FindUniformDeclaration(name);
            if (!decl)
                return;

            FS_CORE_ASSERT(decl, "Could not find uniform with name 'x'");
            auto& buffer = GetUniformBufferTarget(decl);
            buffer.Write((byte*)&value, decl->GetSize(), decl->GetOffset());

            m_OverriddenValues.insert(name);
        }

        void Set(const std::string& name, const SharedRef<Texture>& texture)
        {
            auto decl = m_Material->FindResourceDeclaration(name);
            if (!decl)
            {
                FS_CORE_WARN("Cannot find material property: ", name);
            }
            uint32_t slot = decl->GetRegister();
            if (m_Textures.size() <= slot)
                m_Textures.resize((size_t)slot + 1);
            m_Textures[slot] = texture;
        }

        void Set(const std::string& name, const SharedRef<Texture2D>& texture)
        {
            Set(name, (const SharedRef<Texture>&)texture);
        }

        void Set(const std::string& name, const SharedRef<TextureCube>& texture)
        {
            Set(name, (const SharedRef<Texture>&)texture);
        }

        void Bind();

        uint32_t GetFlags() const { return m_Material->m_MaterialFlags; }
        bool GetFlag(MaterialFlag flag) const { return (uint32_t)flag & m_Material->m_MaterialFlags; }
        void SetFlag(MaterialFlag flag, bool value = true);

        SharedRef<Shader>GetShader() { return m_Material->m_Shader; }
    public:
        static SharedRef<MaterialInstance> Create(const SharedRef<Material>& material);
    private:
        void AllocateStorage();
        void OnShaderReloaded();
        Buffer& GetUniformBufferTarget(ShaderUniformDeclaration* uniformDeclaration);
        void OnMaterialValueUpdated(ShaderUniformDeclaration* decl);
    private:
        SharedRef<Material> m_Material;

        Buffer m_VSUniformStorageBuffer;
        Buffer m_PSUniformStorageBuffer;
        std::vector<SharedRef<Texture>> m_Textures;

        // TODO: This is a temporary system to track overrides
        std::unordered_set<std::string> m_OverriddenValues;
    };

}