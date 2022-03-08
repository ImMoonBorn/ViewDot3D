#pragma once
#include "Event/EventSystem.h"

namespace Core
{
	class MouseScrollEvent : public Event
	{
	private:
		float x, y;
	public:
		MouseScrollEvent(float x, float y)
			:x(x), y(y)
		{
			SetType(EventType::Mouse_Scroll);
		}

		float ScrollX() { return x; }
		float ScrollY() { return y; }
	};
}