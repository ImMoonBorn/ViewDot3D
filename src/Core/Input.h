#pragma once
#include "Core.h"
#include "Keycodes.h"

namespace Core
{
	class Input
	{
	private:
		static glm::vec4 orthoPos;
		static glm::vec2 m_ViewportSize;
		static glm::vec2 m_ViewportPos;
		Input();
		static void OnUpdate();
		friend class Application;
	public:
		static void ScrollCallback(GLFWwindow* window, double x, double y);
		static float GetX();
		static float GetY();
		static float OrthoX();
		static float OrthoY();
		static bool GetKey(const int& key);
		static bool MouseDown(const int& button);
		static bool MouseUp(const int& button);
		static bool Dragging(const int& button);
	};
}