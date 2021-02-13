#pragma once
#include "Farscape/Events/Event.h"


namespace Farscape {
	class FARSCAPE_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Width(width)
			, m_Height(height) {}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << " x " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)	
		EVENT_CLASS_CATEGORY(EC_Application)

	private:
		unsigned int m_Width;
		unsigned int m_Height;
			
	};


	class FARSCAPE_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EC_Application)
	};


	class FARSCAPE_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() {}

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EC_Application)
	};


	class FARSCAPE_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EC_Application)
	};


	class FARSCAPE_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {}

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EC_Application)
	};
}