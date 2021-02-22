#pragma once
#include "Core/Core.h"


namespace Farscape {
    enum class EventType
    {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased, KeyTyped,
        MouseBtnPressed, MouseBtnReleased, MouseMoved, MouseScrolled,
        TimerFired
    };

    enum EventCategory
    {
        None = 0,
        EC_Application          = BIT(0),
        EC_Input                = BIT(1),
        EC_Keyboard             = BIT(2),
        EC_Mouse                = BIT(3),
        EC_MouseBtn             = BIT(4),
        EC_Timer                = BIT(5)
		
		
    };

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
                                virtual EventType GetEventType() const override { return GetStaticType(); }\
                                virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

    class Event : public IEvent
    {
        friend class EventDispatcher;
    public:
        virtual ~Event() = default;

        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;

        // TODO: This should only probably be in DEBUG
        virtual std::string ToString() const { return GetName(); }

        inline bool Handled() { return m_Handled; }

        bool IsInCategory(EventCategory category)
        {
            return GetCategoryFlags() & category;
        }
    protected:
        bool m_Handled = false;
    };

    
    class EventDispatcher
    {
        template<typename T>
        using EventFunction = std::function<bool(T&)>;
    public:
        EventDispatcher(Event& event)
            : m_Event(event) { }

        template<typename T>
        bool Dispatch(const EventFunction<T> func)
        {
            if (m_Event.GetEventType() == T::GetStaticType())
            {
                m_Event.m_Handled |= func(*(T*)&(m_Event));
                return true;
            }
            return false;
        }
    private:
        Event& m_Event;
    };
    

    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.ToString();
    }
}