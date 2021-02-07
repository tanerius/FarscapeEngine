//
//  StateBase.h
//  FarscapeEngine
//
//  Created by Taner Selim on 1/28/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#ifndef StateBase_h
#define StateBase_h

namespace Farscape {

    class MasterRenderer;
    class Application;
    
    class StateBase
    {
    public:
        StateBase(Application& app)
        :   m_pApplication  (&app)
        { }
        
        
        virtual ~StateBase() noexcept = default;
        
        virtual void HandleEvent() = 0;
        virtual void HandleInput() = 0;
        
        virtual void Update(float deltaTime) = 0;
        
        virtual void Render(MasterRenderer* renderer) = 0;

        
    protected:
        Application* m_pApplication;
    };
}

#endif /* StateBase_h */
