#pragma once 

#include "RenderCommand.h"

namespace Farscape {

    class OrthographicCamera;
    class Shader;

    class Renderer : public IRenderer
    {
    public:
        static void BeginScene(OrthographicCamera& camera);
        static void EndScene();

        static void Submit(const Farscape::Ref<Shader>& shader, const Farscape::Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

        static inline RendererAPI::API GetAPI() { return RendererAPI::GetAPI();  }
    private:
        struct SceneData
        {
            glm::mat4 ViewProjectionMatrix;
        };

        static SceneData* s_SceneData;
    
    };
        
}
