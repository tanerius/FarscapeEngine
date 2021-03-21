#pragma once

#include "Scene/Scene.h"


namespace Farscape {

    class SceneHierarchyPanel
    {
    public:
        SceneHierarchyPanel(const SharedRef<Scene>& scene);

        void SetContext(const SharedRef<Scene>& scene);

        void OnImGuiRender();
    private:
        void DrawEntityNode(Entity* entity, uint32_t& imguiEntityID, uint32_t& imguiMeshID);
        void DrawMeshNode(const SharedRef<Mesh>& mesh, uint32_t& imguiMeshID);
        void MeshNodeHierarchy(const SharedRef<Mesh>& mesh, aiNode* node, const glm::mat4& parentTransform = glm::mat4(1.0f), uint32_t level = 0);
    private:
        SharedRef<Scene> m_Context;
        SharedRef<Mesh> m_SelectionContext;
    };

}