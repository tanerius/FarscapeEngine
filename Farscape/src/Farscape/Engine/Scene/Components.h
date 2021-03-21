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
        SharedRef<Farscape::Mesh> Mesh;

        operator SharedRef<Farscape::Mesh>() { return Mesh; }
    };

    struct ScriptComponent
    {
        std::string ModuleName;

    };

    struct CameraComponent
    {
        Camera Cam;
        bool Primary = true;

        operator Camera& () { return Cam; }
        operator const Camera& () const { return Cam; }
    };

    struct SpriteRendererComponent
    {
        glm::vec4 Color = { 1.0f, 1.0f, 1.0f, 1.0f };
        SharedRef<Texture2D> Texture;
        float TilingFactor = 1.0f;
    };


}
