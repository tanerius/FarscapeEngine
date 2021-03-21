#pragma once

#include <glm/glm.hpp>

#include "Renderer/Mesh.h"

namespace Farscape {

    class Entity
    {
    public:
        ~Entity();

        // TODO: Move to Component
        void SetMesh(const SharedRef<Mesh>& mesh) { m_Mesh = mesh; }
        SharedRef<Mesh> GetMesh() { return m_Mesh; }

        void SetMaterial(const SharedRef<MaterialInstance>& material) { m_Material = material; }
        SharedRef<MaterialInstance> GetMaterial() { return m_Material; }

        const glm::mat4& GetTransform() const { return m_Transform; }
        glm::mat4& Transform() { return m_Transform; }

        const std::string& GetName() const { return m_Name; }
    private:
        Entity(const std::string& name);
    private:
        std::string m_Name;
        glm::mat4 m_Transform;

        // TODO: Temp
        SharedRef<Mesh> m_Mesh;
        SharedRef<MaterialInstance> m_Material;

        friend class Scene;
    };

}