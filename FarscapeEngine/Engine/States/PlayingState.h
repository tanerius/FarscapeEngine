//
//  PlayingState.hpp
//  FarscapeEngine
//
//  Created by Taner Selim on 1/28/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#ifndef PlayingState_h
#define PlayingState_h

#include "StateBase.h"
#include "../Player/Player.h"
#include "../Renderer/MasterRenderer.h"


namespace Farscape {
    
    class PlayingState : public StateBase
    {
    public:
        PlayingState(Application& app);
        
        virtual void HandleEvent() override;
        virtual void HandleInput() override;
        
        virtual void Update(float deltaTime) override;
        
        virtual void Render(MasterRenderer* renderer) override;
        
    private:
        Player* m_player;
    };
}


#endif /* PlayingState_h */
