//
//  Farscape.hpp
//  FarscapeEngine
//
//  Created by Taner Selim on 1/25/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#ifndef Farscape_hpp
#define Farscape_hpp

#include <string>

#include "Core/Context.h"
#include "Core/Camera.h"
#include "Renderer/MasterRenderer.h"
#include "Renderer/QuadRenderer.h"
#include "States/StateBase.h"


namespace Farscape
{
    class Event;
    class Application
    {
        public:
            Application(std::string&& name);
            void Start();
            Camera& GetCamera() { return m_camera; }
            const Context GetContext() { return m_Context->GetContext();}
        
            template<typename T, typename... Args>
            void pushState(Args&&... args)
            {
                m_states.push_back(std::make_unique<T>(std::forward<Args>(args)...));
                //auto& s = m_states.back();
            }
            void popState();
            void Test();
        
        protected:
            void Initialize();
            void RunMainLoop();
            void HandleEvents();
            void Shutdown();
        
        
        private:
            ContextWrapper* m_Context = nullptr;
            Event* m_events = nullptr;
            MasterRenderer* m_masterRenderer = nullptr;
            Camera m_camera;
            bool ShutdownRequested;
            bool EnableContextInfo = true;
            QuadRenderer* m_quad;
            double m_TimeSinceAppStart;
        
            std::vector<std::unique_ptr<StateBase>> m_states;
            bool m_isPopState = false;

    };
}

#endif /* Farscape_hpp */

