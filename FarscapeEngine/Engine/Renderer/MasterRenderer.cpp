//
//  MasterRenderer.cpp
//  FarscapeEngine
//
//  Created by Taner Selim on 1/28/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#include "MasterRenderer.h"
#include <GL/glew.h>

void Farscape::MasterRenderer::DrawMesh(const Vector3d& pos)
{
    m_MeshRenderer->AddMesh(pos);
}
void Farscape::MasterRenderer::FinishRender(const Camera* camera)
{
    glClearColor(0.1, 0.5, 1.0, 1.0);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    m_MeshRenderer->RenderMeshes(camera);
}
