//
//  cgentity.hpp
//  FarscapeEngine
//
//  Created by Taner Selim on 4/16/17.
//  Copyright © 2017 Taner Selim. All rights reserved.
//

#ifndef cgentity_hpp
#define cgentity_hpp
#ifdef WINDOWS
#include<windows.h>
#endif

#include "cgcore.hpp"

#ifdef USE_GLM
    #include <glm/glm.hpp>
#endif

#include <GL/glew.h>

namespace CGCore
{
    class Mesh;
    class Texture;
    class Transform;

    // Container wit a model together with the transform matrix
    class Entity : public Object
    {
        private:
        Mesh* m_Mesh = nullptr;
        Texture* m_Texture = nullptr;
        Transform* m_Transform = nullptr;
    
        public:
        // Binds texture to texture unit 0
        Entity(const char* objModelPath, const char* texturePath, Transform* defTransform = nullptr);
        Entity(const char* objModelPath, Texture* texture, Transform* defTransform = nullptr);
        Entity(); // default entity maybe a triangle
        virtual ~Entity();
        
        Mesh* GetMesh() { return m_Mesh; }
        Texture* GetTexture() { return m_Texture; }
        Transform* GetTransform() { return m_Transform; }
        
        // Set and activate a texture
        void SetTexture(Texture* t) { m_Texture = t; }
        
        virtual std::string ToString() const override;

        
    };
}
#endif /* cgentity_hpp */
