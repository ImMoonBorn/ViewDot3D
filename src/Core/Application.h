#pragma once
#include "Window.h"
#include "Event/EventSystem.h"
#include "Event/Events.h"
#include "Layer.h"
#include "Timestep.h"

namespace Core
{
	class Application
	{
	private:
		static Application* m_Instance;
		std::list<Layer*> m_Layers;
		void OnEvent(Event& e);
	public:
		Application();
		static void DeployEvent(Event& event) { m_Instance->OnEvent(event); }
		void AddLayer(Layer* layer);
		void RemoveLayer(Layer* layer);
		void Run();
	};
}