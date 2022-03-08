#pragma once
#include "Event/Events.h"

namespace Core
{
	class Layer
	{
	public:
		virtual void OnEvent(Event& event) {};
		virtual void OnAttach() {};
		virtual void OnUpdate() {};
		virtual void OnDrawGui() {};
		virtual void OnDetach() {};
	};
}