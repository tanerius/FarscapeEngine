//
//  Event.hpp
//  FarscapeEngine
//
//  Created by Taner Selim on 1/26/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#ifndef Event_h
#define Event_h

#include "../Util/SingletonBase.h"

#define MAX_HANDLED_KEYS 1024

// Forward declarations
class GLFWwindow;

namespace Farscape
{
    class Event : public Farscape::SingletonBase<Event>
    {
        friend class Farscape::SingletonBase<Event>;
        public:
            Event() = default;
            // Checks the state of the key buffer
            bool CheckPressed(const int& key);
            // Checks the key state and resets it to unpressed
            bool CheckOncePressed(const int& key);
            // Statics
        
            // Keyboard state
            static bool HandledKeys[MAX_HANDLED_KEYS];
            // Error event callback
            static void ErrorCallback(int error, const char* description);
            // Keyboard event callback
            static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    };
}

#endif /* Event_h */
