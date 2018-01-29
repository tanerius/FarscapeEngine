//
//  Player.hpp
//  FarscapeEngine
//
//  Created by Taner Selim on 1/28/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#ifndef Player_h
#define Player_h

#include "../Math/Definitions.h"
#include "../Core/Entity.h"

namespace Farscape {
    class Player : public Entity
    {
    public:
        Player();
        
        void HandleInput();
        
        void Update(float dt);
        
    private:
        void KeyboardInput();
        void MouseInput();
        
        Vector3d m_velocity;
    };
}

#endif /* Player_h */
