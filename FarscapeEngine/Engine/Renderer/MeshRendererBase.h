//
//  Header.h
//  FarscapeEngine
//
//  Created by Taner Selim on 1/28/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#ifndef MeshRendererBase_h
#define MeshRendererBase_h

#include "../Math/Definitions.h"
#include "../Core/Camera.h"

namespace Farscape {
    class MeshRendererBase
    {
    public:
        virtual void AddMesh(const Vector3d& position) = 0;
        virtual void RenderMeshes(const Camera& camera) = 0;
    };
}

#endif /* Header_h */
