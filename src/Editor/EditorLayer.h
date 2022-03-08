#pragma once

#include "Core.h"
#include "Renderer/Frambuffer.h"

namespace Core::Utils
{
	class CameraControllerPerspective;
}

namespace Core
{
	class Scene;

	class EditorLayer : public Layer
	{
	private:
		Framebuffer* m_Framebuffer = nullptr;
		Scene* m_Scene;
		Utils::CameraControllerPerspective* m_Controller;
		ImVec2 m_ViewportSize;
		glm::vec2 m_ViewportPos;
		float m_AspectRatio;

		void Viewport(bool& open);
		void LightingSettings(bool& open);
		void MaterialView(bool& open);
		void Debug(bool& open);

	public:
		void OnAttach();
		void OnUpdate();
		void OnDetach();
		void OnEvent(Event& event);
		void OnDrawGui();
	};
}