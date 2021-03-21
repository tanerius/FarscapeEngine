#pragma once

#include "Entity.h"
#include "Renderer/Camera.h"

namespace Farscape {

    struct Environment
    {
        SharedRef<TextureCube> RadianceMap;
        SharedRef<TextureCube> IrradianceMap;

        static Environment Load(const std::string& filepath);
    };

    struct Light
    {
        glm::vec3 Direction;
        glm::vec3 Radiance;

        float Multiplier = 1.0f;
    };

    class Scene : public RefCounter
    {
    public:
        Scene(const std::string& debugName = "Scene");
        ~Scene();

        void Init();

        void OnUpdate(Timestep ts);
        void OnEvent(Event& e);

        void SetCamera(const Camera& camera);
        Camera& GetCamera() { return m_Camera; }

        void SetEnvironment(const Environment& environment);
        void SetSkybox(const SharedRef<TextureCube>& skybox);

        Light& GetLight() { return m_Light; }

        float& GetSkyboxLod() { return m_SkyboxLod; }

        void AddEntity(Entity* entity);
        Entity* CreateEntity(const std::string& name = "");
    private:
        std::string m_DebugName;
        std::vector<Entity*> m_Entities;
        Camera m_Camera;

        Light m_Light;
        float m_LightMultiplier = 0.3f;

        Environment m_Environment;
        SharedRef<TextureCube> m_SkyboxTexture;
        SharedRef<MaterialInstance> m_SkyboxMaterial;

        float m_SkyboxLod = 1.0f;

        friend class SceneRenderer;
        friend class SceneHierarchyPanel;
    };

}