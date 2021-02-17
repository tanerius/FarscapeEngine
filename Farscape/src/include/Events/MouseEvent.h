#pragma once
#include "Event.h"

namespace Farscape {
	class FARSCAPE_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			: m_Xpos(x)
			, m_Ypos(y) {}

		inline float GetX() const { return m_Xpos; }
		inline float GetY() const { return m_Ypos; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_Xpos << ", " << m_Ypos;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EC_Mouse | EC_Input)
	private:
		float m_Xpos, m_Ypos;
	};


	class FARSCAPE_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float x, float y)
			: m_Xoffset(x)
			, m_Yoffset(y) {}

		inline float GetXoffset() const { return m_Xoffset; }
		inline float GetYoffset() const { return m_Yoffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_Xoffset << ", " << m_Yoffset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EC_Mouse | EC_Input)
	private:
		float m_Xoffset, m_Yoffset;
	};


	// No direct initialize
	class FARSCAPE_API MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return m_Button; }
		EVENT_CLASS_CATEGORY(EC_Mouse | EC_Input)
	protected:
		MouseButtonEvent(int btn)
			: m_Button(btn) {}

		int m_Button;
	};


	class FARSCAPE_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int btn)
			: MouseButtonEvent(btn) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button ;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseBtnPressed)
	};


	class FARSCAPE_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int btn)
			: MouseButtonEvent(btn) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseBtnReleased)
	};
}