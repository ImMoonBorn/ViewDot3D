#pragma once
#include "Camera.h"
#include "glm/glm.hpp"

namespace Core::Utils
{
	class CameraControllerPerspective
	{
	private:
		Camera& m_Camera;
		float m_MoveSpeed = 1.0f;
		float m_RotateSpeed = 100.0f;
		float m_ZoomSpeed = 10.0f;
		glm::vec3 m_Position;
		glm::vec2 m_Rotation;
		bool OnMouseScroll(Event& event);
	public:
		CameraControllerPerspective(Camera& camera);
		~CameraControllerPerspective() = default;
		void OnUpdate();
		void OnEvent(Event& event);
		void OnDrawGui();
	};
}