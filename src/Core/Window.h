#pragma once
#include "Core.h"

namespace Core
{
	class Window
	{
	private:
		Window() = default;
		static GLFWwindow* m_GLWindow;
		static std::string m_Name;
		static uint32_t m_Width;
		static uint32_t m_Height;
		static void window_size_callback(GLFWwindow* window, int width, int height);
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	public:
		static int Create(std::string name, uint32_t width, uint32_t height);
		static void OnUpdate();
		static bool IsWindowRunning() { return !glfwWindowShouldClose(m_GLWindow); }
		static unsigned int GetWidth() { return m_Width; }
		static unsigned int GetHeight() { return m_Height; }
		static float AspectRatio() { return (float)m_Width / (float)m_Height; }
		static GLFWwindow* GetNativeWindow() { return m_GLWindow; }
		static void Destroy() { glfwTerminate(); DebugSys("Window Destroyed"); }
	};
}