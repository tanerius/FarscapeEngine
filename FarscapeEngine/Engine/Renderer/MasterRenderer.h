//
//  MasterRenderer.hpp
//  FarscapeEngine
//
//  Created by Taner Selim on 1/28/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#ifndef MasterRenderer_h
#define MasterRenderer_h

#include "../Math/Definitions.h"
#include "MeshRendererBase.h"
#include <GL/glew.h>

namespace Farscape {
    class Camera;
    
    class MasterRenderer
    {
        private:
            MeshRendererBase* m_MeshRenderer;
        public:
        MasterRenderer() = delete;
        MasterRenderer(MeshRendererBase* m) : m_MeshRenderer(m) {}
        void DrawMesh(const Vector3d& pos);
        void FinishRender(const Camera& camera);
    };
    
    
}

#endif /* MasterRenderer_h */
