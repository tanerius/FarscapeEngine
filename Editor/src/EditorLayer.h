#pragma once

#include "Farscape.h"

#include "ImGui/ImGuiLayer.h"
#include <imgui_internal.h>

#pragma warning(disable:4201)
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#pragma warning(default:4201)

#include <string>

#include "Editor/SceneHierarchyPanel.h"

namespace Farscape {

    class EditorLayer : public Layer
    {
    public:
        enum class PropertyFlag
        {
            None = 0, ColorProperty = 1
        };
    public:
        EditorLayer();
        virtual ~EditorLayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdate(Timestep ts) override;

        virtual void OnImGuiRender() override;
        virtual void OnEvent(Event& e) override;
        bool OnKeyPressedEvent(KeyPressedEvent& e);
        bool OnMouseButtonPressed(MouseButtonPressedEvent& e);

        // ImGui UI helpers
        bool Property(const std::string& name, bool& value);
        void Property(const std::string& name, float& value, float min = -1.0f, float max = 1.0f, PropertyFlag flags = PropertyFlag::None);
        void Property(const std::string& name, glm::vec2& value, PropertyFlag flags);
        void Property(const std::string& name, glm::vec2& value, float min = -1.0f, float max = 1.0f, PropertyFlag flags = PropertyFlag::None);
        void Property(const std::string& name, glm::vec3& value, PropertyFlag flags);
        void Property(const std::string& name, glm::vec3& value, float min = -1.0f, float max = 1.0f, PropertyFlag flags = PropertyFlag::None);
        void Property(const std::string& name, glm::vec4& value, PropertyFlag flags);
        void Property(const std::string& name, glm::vec4& value, float min = -1.0f, float max = 1.0f, PropertyFlag flags = PropertyFlag::None);

        void ShowBoundingBoxes(bool show, bool onTop = false);
    private:
        std::pair<float, float> GetMouseViewportSpace();
        std::pair<glm::vec3, glm::vec3> CastRay(float mx, float my);
    private:
        Scope<SceneHierarchyPanel> m_SceneHierarchyPanel;

        SharedRef<Scene> m_Scene;
        SharedRef<Scene> m_SphereScene;
        SharedRef<Scene> m_ActiveScene;

        Entity* m_MeshEntity = nullptr;

        SharedRef<Shader> m_BrushShader;
        SharedRef<Mesh> m_PlaneMesh;
        SharedRef<Material> m_SphereBaseMaterial;

        SharedRef<Material> m_MeshMaterial;

        std::vector<SharedRef<MaterialInstance>> m_MetalSphereMaterialInstances;
        std::vector<SharedRef<MaterialInstance>> m_DielectricSphereMaterialInstances;

        float m_GridScale = 16.025f, m_GridSize = 0.025f;

        struct AlbedoInput
        {
            glm::vec3 Color = { 0.972f, 0.96f, 0.915f }; // Silver, from https://docs.unrealengine.com/en-us/Engine/Rendering/Materials/PhysicallyBased
            SharedRef<Texture2D> TextureMap;
            bool SRGB = true;
            bool UseTexture = false;
        };
        AlbedoInput m_AlbedoInput;

        struct NormalInput
        {
            SharedRef<Texture2D> TextureMap;
            bool UseTexture = false;
        };
        NormalInput m_NormalInput;

        struct MetalnessInput
        {
            float Value = 1.0f;
            SharedRef<Texture2D> TextureMap;
            bool UseTexture = false;
        };
        MetalnessInput m_MetalnessInput;

        struct RoughnessInput
        {
            float Value = 0.2f;
            SharedRef<Texture2D> TextureMap;
            bool UseTexture = false;
        };
        RoughnessInput m_RoughnessInput;

        // PBR params
        bool m_RadiancePrefilter = false;

        float m_EnvMapRotation = 0.0f;

        enum class SceneType : uint32_t
        {
            Spheres = 0, Model = 1
        };
        SceneType m_SceneType;

        // Editor resources
        SharedRef<Texture2D> m_CheckerboardTex;

        glm::vec2 m_ViewportBounds[2];
        int m_GizmoType = -1; // -1 = no gizmo
        float m_SnapValue = 0.5f;
        bool m_AllowViewportCameraEvents = false;
        bool m_DrawOnTopBoundingBoxes = false;

        bool m_UIShowBoundingBoxes = false;
        bool m_UIShowBoundingBoxesOnTop = false;

        struct SelectedSubmesh
        {
            Submesh* Mesh;
            float Distance;
        };
        std::vector<SelectedSubmesh> m_SelectedSubmeshes;
        glm::mat4* m_CurrentlySelectedTransform = nullptr;
    };

}
