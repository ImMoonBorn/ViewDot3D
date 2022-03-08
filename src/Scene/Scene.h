#pragma once
#include "Core.h"
#include "Utils/Camera.h"

namespace Core
{
	class Scene
	{
	private:
		Utils::Camera* m_Camera;
	public:
		Scene();
		~Scene() = default;
		void OnLoad();
		void OnUpdate();
		void OnEvent(Event& event);
		Utils::Camera& GetCam() { return *m_Camera; }
	};
}