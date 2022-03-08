#include "pch.h"
#include "CameraControllerPerspective.h"
#include "Core/Input.h"
#include "imgui/imgui.h"

namespace Core::Utils
{
	CameraControllerPerspective::CameraControllerPerspective(Camera& camera)
		:m_Camera(camera), m_Position(0.0f, 3.5f, 3.5f), m_Rotation(-30.0f, -90.0f)
	{}

	void CameraControllerPerspective::OnUpdate()
	{
		if (Input::GetKey(KEY_LEFT_SHIFT))
		{
			m_MoveSpeed = 10.0f;
			m_RotateSpeed = 200.0f;
			m_ZoomSpeed = 20.0f;
		}
		else
		{
			m_MoveSpeed = 2.0f;
			m_RotateSpeed = 75.0f;
			m_ZoomSpeed = 10.0f;
		}

		if (Input::GetKey(KEY_Q))
			m_Rotation.y += m_RotateSpeed * Time::DeltaTime();
		else  if (Input::GetKey(KEY_E))
			m_Rotation.y -= m_RotateSpeed * Time::DeltaTime();

		if (Input::GetKey(KEY_W))
			m_Position += m_Camera.FRONT * m_MoveSpeed * Time::DeltaTime();
		else if (Input::GetKey(KEY_S))
			m_Position -= m_Camera.FRONT * m_MoveSpeed * Time::DeltaTime();
	
		if (Input::GetKey(KEY_A))
			m_Position -= m_Camera.RIGHT * m_MoveSpeed * Time::DeltaTime();
		else if (Input::GetKey(KEY_D))
			m_Position += m_Camera.RIGHT * m_MoveSpeed * Time::DeltaTime();

		m_Camera.SetView(m_Position, m_Rotation.x, m_Rotation.y);
	}

	void CameraControllerPerspective::OnEvent(Event& event)
	{
		EventHandler handler = { event };
		handler.HandleEvent(EventType::Mouse_Scroll, EVENT_F_POINTER(OnMouseScroll));
	}

	bool CameraControllerPerspective::OnMouseScroll(Event& event)
	{
		MouseScrollEvent& e = (MouseScrollEvent&)event;
		if (Input::GetKey(KEY_LEFT_CONTROL))
		{
			if (e.ScrollY() > 0)
				m_Rotation.x -= m_RotateSpeed * Time::DeltaTime();
			else
				m_Rotation.x += m_RotateSpeed * Time::DeltaTime();
		}
		else
		{
			if (e.ScrollY() > 0)
				m_Position -= m_Camera.UP * m_ZoomSpeed * Time::DeltaTime();
			else
				m_Position += m_Camera.UP * m_ZoomSpeed * Time::DeltaTime();
		}
		return false;
	}

	void CameraControllerPerspective::OnDrawGui()
	{
#if 1
		ImGui::Begin("Camera Controller");
		ImGui::SliderFloat3("Position", &m_Position[0], -100.0f, 100.0f);
		ImGui::SliderFloat2("Rotation", &m_Rotation[0], -90.0f, 90.0f);
		ImGui::End();
#endif
	}
}