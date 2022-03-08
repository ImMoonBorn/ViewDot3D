#include "pch.h"
#include "Core.h"
#include "Editor/EditorLayer.h"
#include <wtypes.h>

class Sandbox : public Core::Application
{
public:
	Sandbox()
	{
		AddLayer(new Core::EditorLayer());
	};
	~Sandbox() = default;
};

#if _DEBUG
int main()
{
	Sandbox* app = new Sandbox();
	app->Run();
	delete app;
}

#else

int WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd
)
{
	Sandbox* app = new Sandbox();
	app->Run();
	delete app;
}
#endif