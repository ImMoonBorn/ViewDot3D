#include "pch.h"
#include "Input.h"

namespace Core
{
	glm::vec4 Input::orthoPos;
	glm::vec2 Input::m_ViewportSize;
	glm::vec2 Input::m_ViewportPos;

	void Input::ScrollCallback(GLFWwindow* window, double x, double y)
	{
		MouseScrollEvent event{ (float)x, (float)y };
		Application::DeployEvent(event);
	}

	float Input::GetX()
	{
		double x, y;
		glfwGetCursorPos(Window::GetNativeWindow(), &x, &y);
		return (float)x;
	}

	float Input::GetY()
	{
		double x, y;
		glfwGetCursorPos(Window::GetNativeWindow(), &x, &y);
		return (float)y;
	}

	bool Input::MouseDown(const int& button)
	{
		switch (button)
		{
			case 0:
			{
				int state = glfwGetMouseButton(Window::GetNativeWindow(), GLFW_MOUSE_BUTTON_LEFT);
				if (state == GLFW_PRESS)
					return true;
				else
					return false;
			}
			case 1:
			{
				int state = glfwGetMouseButton(Window::GetNativeWindow(), GLFW_MOUSE_BUTTON_RIGHT);
				if (state == GLFW_PRESS)
					return true;
				else
					return false;
			}
			case 2:
			{
				int state = glfwGetMouseButton(Window::GetNativeWindow(), GLFW_MOUSE_BUTTON_MIDDLE);
				if (state == GLFW_PRESS)
					return true;
				else
					return false;
			}
			default:
				return false;
		}
	}

	bool Input::MouseUp(const int& button)
	{
		switch (button)
		{
			case 0:
			{
				int state = glfwGetMouseButton(Window::GetNativeWindow(), GLFW_MOUSE_BUTTON_LEFT);
				if (state == GLFW_RELEASE)
					return true;
				else
					return false;
			}
			case 1:
			{
				int state = glfwGetMouseButton(Window::GetNativeWindow(), GLFW_MOUSE_BUTTON_RIGHT);
				if (state == GLFW_RELEASE)
					return true;
				else
					return false;
			}
			case 2:
			{
				int state = glfwGetMouseButton(Window::GetNativeWindow(), GLFW_MOUSE_BUTTON_MIDDLE);
				if (state == GLFW_RELEASE)
					return true;
				else
					return false;
			}
			default:
				return false;
		}
	}

	bool Input::Dragging(const int& button)
	{
		return MouseDown(button);
	}

	float Input::OrthoX()
	{
		return orthoPos.x;
	}

	float Input::OrthoY()
	{
		return orthoPos.y;
	}

	bool Input::GetKey(const int& key)
	{
		if (glfwGetKey(Window::GetNativeWindow(), key) == GLFW_PRESS)
			return true;
		return false;
	}

	void Input::OnUpdate()
	{
		m_ViewportSize = glm::vec2(Window::GetWidth(), Window::GetHeight());
		m_ViewportPos = glm::vec2(0.0f, 0.0f);
		glm::mat4 inverseMat = glm::inverse(Renderer::ViewProjection());
		float x = (2.0f * ((float)(GetX() - m_ViewportPos.x) / (m_ViewportSize.x - 0))) - 1.0f;
		float y = (2.0f * (1.0f - ((float)(GetY() - m_ViewportPos.y) / (m_ViewportSize.y - 0)))) - 1.0f;
		orthoPos = glm::vec4(x, y, 0.0f, 1.0f);
		orthoPos = inverseMat * orthoPos;
	}
}