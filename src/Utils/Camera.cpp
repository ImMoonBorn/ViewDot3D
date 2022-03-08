#include "pch.h"
#include "Camera.h"

#include "Core/Window.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Core::Utils
{
	Camera* Camera::Main = nullptr;

	Camera::Camera()
		:m_Position(0.0f, 1.0f, 3.0f), m_Projection(1.0f), m_View(1.0f)
	{
		Main = this;
		RecalculateProjMatrix(static_cast<float>(Window::GetWidth()), static_cast<float>(Window::GetWidth()));
		RecalculateViewMatrix();
	}

	Camera::Camera(const glm::vec3& pos)
		:m_Position(pos), m_Projection(1.0f), m_View(1.0f)
	{
		Main = this;
		RecalculateProjMatrix(static_cast<float>(Window::GetWidth()), static_cast<float>(Window::GetWidth()));
		RecalculateViewMatrix();
	}

	void Camera::RecalculateViewMatrix()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		front.y = sin(glm::radians(m_Pitch));
		front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		FRONT = glm::normalize(front);
		
		RIGHT = glm::normalize(glm::cross(FRONT, glm::vec3(.0f, 1.0f, .0f)));  
		UP = glm::normalize(glm::cross(RIGHT, FRONT));

		glm::mat4 view = glm::lookAt(m_Position, m_Position + FRONT, UP);
		m_View = view;
		m_ViewProjection = m_Projection * m_View;
	}

	void Camera::RecalculateProjMatrix(float width, float height)
	{
		m_Projection = glm::perspective(glm::radians(60.0f), width/height, 0.1f, 100.0f);
	}

	void Camera::SetView(const glm::vec3& pos, const float& pitch, const float& yaw)
	{
		m_Position = pos;
		m_Yaw = yaw;
		m_Pitch = pitch;

		if (m_Pitch > 89.0f)
			m_Pitch = 89.0f;
		if (m_Pitch < -89.0f)
			m_Pitch = -89.0f;

		RecalculateViewMatrix();
	}
}