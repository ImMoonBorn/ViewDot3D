#pragma once
#include "Core.h"

namespace Core
{
	struct ImGuiLayer
	{
	public:
		static void Init();
		static void BeginRender();
		static void EndRender();
		static void OnEvent(Event& e);
	private:
		static bool OnMouseScrolled(Event& e);
	};
}