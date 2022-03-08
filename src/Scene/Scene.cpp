#include "pch.h"
#include "Scene.h"
#include "Renderer/Renderer.h"
#include "Utils/Camera.h"

using namespace Core::Utils;

namespace Core
{
	Scene::Scene()
		:m_Camera(new Camera())
	{
	}

	void Scene::OnLoad()
	{
		DebugSys("Scene Loaded");
	}

	void Scene::OnUpdate()
	{
	}

	void Scene::OnEvent(Event& event)
	{
	}
}