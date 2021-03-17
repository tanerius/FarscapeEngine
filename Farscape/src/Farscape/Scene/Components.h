#pragma once

#include <glm/glm.hpp>

#include "Renderer/Texture.h"
#include "Renderer/Mesh.h"
#include "Renderer/Camera.h"

namespace Farscape {

    struct TagComponent
    {
        std::string Tag;

        operator std::string& () { return Tag; }
        operator const std::string& () const { return Tag; }
    };

    struct TransformComponent
    {
        glm::mat4 Transform;

        operator glm::mat4& () { return Transform; }
        operator const glm::mat4& () const { return Transform; }
    };

    struct MeshComponent
    {
        Ref<Farscape::Mesh> Mesh;

        operator Ref<Farscape::Mesh>() { return Mesh; }
    };

    struct ScriptComponent
    {
        // TODO: C# script
        std::string ModuleName;
    };

    struct CameraComponent
    {
        //OrthographicCamera Camera;
        Farscape::Camera Camera;
        bool Primary = true;

        operator Farscape::Camera& () { return Camera; }
        operator const Farscape::Camera& () const { return Camera; }
    };

    struct SpriteRendererComponent
    {
        glm::vec4 Color = { 1.0f, 1.0f, 1.0f, 1.0f };
        Ref<Texture2D> Texture;
        float TilingFactor = 1.0f;
    };


}
