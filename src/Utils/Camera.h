#pragma once
#include "Event/Events.h"
#include "glm/glm.hpp"

namespace Core::Utils
{
	class Camera
	{
	private:
		static Camera* Main;
		float m_Yaw = -90.0f;
		float m_Pitch = 0.0f;

		glm::vec3 m_Position;
		glm::vec3 m_Direction = glm::vec3{ 0.0f };
		glm::mat4 m_View;
		glm::mat4 m_Projection;
		glm::mat4 m_ViewProjection;
		float m_Rotation = 0.0f;
	public:
		glm::vec3 UP = glm::vec3{ 0.0f, 1.0f, 0.0f };
		glm::vec3 FRONT = glm::vec3{ 0.0f, 0.0f, -1.0f };
		glm::vec3 RIGHT = glm::vec3{ 0.0f, 0.0f, 0.0f };
		Camera();
		Camera(const glm::vec3& pos);
		~Camera() = default;
		void SetView(const glm::vec3& pos, const float& pitch, const float& yaw);
		glm::mat4& GetVP() { return m_ViewProjection; }
		static glm::vec3& CamPosition() { return Main->m_Position; }

		void RecalculateViewMatrix();
		void RecalculateProjMatrix(float width, float height);
	};
}