//
//  CubeRenderer.hpp
//  FarscapeEngine
//
//  Created by Taner Selim on 2/4/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#ifndef CubeRenderer_h
#define CubeRenderer_h

#include "../Core/Model.h"
#include "../Core/Transform.h"
#include "../Math/Definitions.h"
#include "../Shaders/BasicShader.h"
#include "../Texture/BasicTexture.h"
#include "../Texture/TextureAtlas.h"
#include "MeshRendererBase.h"

namespace Farscape
{
 
    
    class Camera;
    
    class CubeRenderer :  public MeshRendererBase
    {
    public:
        CubeRenderer();
        ~CubeRenderer();
        
        virtual void AddMesh(const Vector3d& position, const Vector3d& rot, const Vector3d& scale) override;
        virtual void RenderMeshes(const Camera* camera) override;
        
    private:
        std::vector<std::unique_ptr<Transform>> m_quads;
        
        Model* m_quadModel;
        
        BasicShader* m_shader;
        BasicTexture* m_basicTexture;
        TextureAtlas* m_atlasTest;
    };
    
}


#endif /* CubeRenderer_h */
