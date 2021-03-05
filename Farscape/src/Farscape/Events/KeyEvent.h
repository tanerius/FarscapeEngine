#pragma once

#include "Event.h"

#include <sstream>
#include <string>

namespace Farscape {

    class FARSCAPE_API KeyEvent : public Event
    {
    public:
        inline unsigned int GetKeyCode() const { return m_KeyCode; }
        EVENT_CLASS_CATEGORY(EC_Keyboard | EC_Input)
    protected:
        unsigned int m_KeyCode;

        // Constructor un protected to prevent direct initialization via this ctor
        KeyEvent(unsigned int keycode) 
            : m_KeyCode(keycode) {}
    };


    class FARSCAPE_API KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(unsigned int keycode, int repeatCount)
            : KeyEvent(keycode)
            , m_RepeatCount(repeatCount) {}

        inline int GetRepeatCount() const { return m_RepeatCount; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_KeyCode << " x " << m_RepeatCount;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)

    protected:
        int m_RepeatCount;

    };


    class FARSCAPE_API KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(unsigned int keycode)
            : KeyEvent(keycode) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_KeyCode;
            return ss.str();
        }
        
        EVENT_CLASS_TYPE(KeyReleased)
    };

    class FARSCAPE_API KeyTypedEvent : public KeyEvent
    {
    public:
        KeyTypedEvent(unsigned int keycode)
            : KeyEvent(keycode) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyTypedEvent: " << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };
}