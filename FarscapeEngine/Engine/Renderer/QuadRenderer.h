//
//  QuadRenderer.hpp
//  FarscapeEngine
//
//  Created by Taner Selim on 1/28/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#ifndef QuadRenderer_h
#define QuadRenderer_h

#include <vector>

#include "../Core/Model.h"
#include "../Math/Definitions.h"
#include "../Shaders/BasicShader.h"
#include "../Texture/BasicTexture.h"
#include "../Core/Transform.h"
#include "MeshRendererBase.h"

namespace Farscape {
    class Camera;
    class QuadRenderer :  public MeshRendererBase
    {
        public:
            QuadRenderer();
            ~QuadRenderer();
        
            virtual void AddMesh(const Vector3d& position, const Vector3d& rot, const Vector3d& scale) override;
            virtual void RenderMeshes(const Camera* camera) override;
        
        private:
            std::vector<std::unique_ptr<Transform>> m_quads;
        
            Model* m_quadModel;
            BasicShader* m_shader;
            BasicTexture* m_basicTexture;
        
    };
}

#endif /* QuadRenderer_h */
