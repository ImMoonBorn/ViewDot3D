#include "pch.h"
#include "Application.h"
#include "Renderer/Renderer.h"
#include "ImGuiLayer.h"

namespace Core
{
	Application* Application::m_Instance;

	Application::Application()
	{
		if (!m_Instance)
			m_Instance = this;
		else
		{
			DebugErr("Application already exists!");
			return;
		}

		if (Window::Create("ViewDot 3D", 1600, 900))
			DebugSys("Window Created Successfully");
		else
			DebugErr("Window Creation Failed!");
	}
	
	void Application::AddLayer(Layer* layer)
	{
		m_Layers.push_back(layer);
		layer->OnAttach();
	}
	
	void Application::RemoveLayer(Layer* layer)
	{
		m_Layers.remove(layer);
		layer->OnDetach();
	}

	void Application::OnEvent(Event& e)
	{
		for (auto l = m_Layers.end(); l != m_Layers.begin();)
			(*--l)->OnEvent(e);
		ImGuiLayer::OnEvent(e);
	}
	
	void Application::Run()
	{
		float end = (float)glfwGetTime();
		float begin = 0.0f;
		float dt = 0.0f;
		float timer = 10.0f;

		Renderer::Awake();
		ImGuiLayer::Init();

		DebugSys("Application Run Started");

		while (Window::IsWindowRunning())
		{
			begin = (float)glfwGetTime();
			dt = begin - end;
			end = begin;
			Time::m_DeltaTime = dt;

			Renderer::Clear();
			for (Layer* layer : m_Layers)
				layer->OnUpdate();

			ImGuiLayer::BeginRender();
			for (Layer* layer : m_Layers)
				layer->OnDrawGui();
			ImGuiLayer::EndRender(); 

			Window::OnUpdate();
			Input::OnUpdate();
		}
		Window::Destroy();
	}
}
