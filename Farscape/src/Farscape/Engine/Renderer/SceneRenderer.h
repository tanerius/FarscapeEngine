#pragma once

#include "Scene/Scene.h"
#include "Renderer/Mesh.h"
#include "RenderPass.h"

namespace Farscape {

    struct SceneRendererOptions
    {
        bool ShowGrid = true;
        bool ShowBoundingBoxes = false;
    };

    class SceneRenderer
    {
    public:
        static void Init();

        static void SetViewportSize(uint32_t width, uint32_t height);

        static void BeginScene(const Scene* scene);
        static void EndScene();

        static void SubmitEntity(Entity* entity);

        static std::pair<SharedRef<TextureCube>, SharedRef<TextureCube>> CreateEnvironmentMap(const std::string& filepath);

        static SharedRef<RenderPass> GetFinalRenderPass();
        static SharedRef<Texture2D> GetFinalColorBuffer();

        // TODO: Temp
        static uint32_t GetFinalColorBufferRendererID();

        static SceneRendererOptions& GetOptions();
    private:
        static void FlushDrawList();
        static void GeometryPass();
        static void CompositePass();
    };

}