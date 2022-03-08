#include "pch.h"
#include "EditorLayer.h"
#include "Core.h"
#include "Utils/CameraControllerPerspective.h"
#include "Renderer/Texture.h"
#include "Renderer/Mesh.h"
#include <imgui/Extensions/ImFileBrowser/imfilebrowser.h>
#include "Renderer/Light.h"

using namespace Core;
using namespace Utils;

namespace Core
{
	Mesh* mesh;
	Light* light;
	Texture* m_Diffuse = nullptr;
	Texture* m_Specular = nullptr;
	glm::vec3 ambientLight = { 0.2f, 0.2f, 0.2f };

	void EditorLayer::OnAttach()
	{
		m_Scene = new Scene();
		Renderer::LightConfig(false ,ambientLight);
		light = new Light();
		m_Framebuffer = new Framebuffer();
		m_Controller = new CameraControllerPerspective(m_Scene->GetCam());
		m_Scene->OnLoad();
	}

	void EditorLayer::OnEvent(Event& event)
	{
		m_Scene->OnEvent(event);
		m_Controller->OnEvent(event);
	}

	void EditorLayer::OnUpdate()
	{
		m_Scene->OnUpdate();
		m_Controller->OnUpdate();

		if (m_ViewportSize.x != m_Framebuffer->GetWidth() || m_ViewportSize.y != m_Framebuffer->GetHeight())
		{
			float width = m_ViewportSize.x;
			float height = m_ViewportSize.y;
			m_Framebuffer->Resize((uint32_t)width,(uint32_t)height);
			m_Scene->GetCam().RecalculateProjMatrix((float) width,(float) height);
		}

		Renderer::Begin(m_Scene->GetCam().GetVP(), *m_Framebuffer);
		{
			Renderer::DrawLight(*light);
			if (mesh != nullptr)
			{
				mesh->Position = glm::vec3(0.0f, -2.0f, 0.0f);
				Renderer::DrawMesh(*mesh);
			}
		}
		Renderer::End(*m_Framebuffer);
	}

	void EditorLayer::OnDrawGui()
	{
		static bool viewportOpen = true;
		static bool lightsOpen = true;
		static bool viewMaterial = true;
		static bool debug = true;

		//DOCKSPACE
		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;
		
		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

		ImGui::Begin("DockSpace", nullptr, window_flags);
		
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		static ImGui::FileBrowser fileBrowser;
		fileBrowser.SetTitle("File Browser");
		fileBrowser.SetTypeFilters({ ".obj" });

		ImGui::BeginMainMenuBar();
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open"))
					fileBrowser.Open();

				if (ImGui::MenuItem("Close"))
				{
					if (mesh != nullptr)
					{
						delete mesh;
						mesh = nullptr;
					}
					if (m_Diffuse != nullptr)
					{
						delete m_Diffuse;
						m_Diffuse = nullptr;
					}
					if (m_Specular != nullptr)
					{
						delete m_Specular;
						m_Specular = nullptr;
					}
				}
				ImGui::EndMenu();
			}
			fileBrowser.Display();

			if (fileBrowser.HasSelected())
			{
				if(mesh != nullptr)
					delete mesh;
				mesh = new Mesh(fileBrowser.GetSelected().string());
				fileBrowser.ClearSelected();
			}

			if (ImGui::BeginMenu("View", true))
			{
				if (ImGui::MenuItem("Viewport", " ", viewportOpen, true))
					viewportOpen = !viewportOpen;

				if (ImGui::MenuItem("Lighting Settings", " ", lightsOpen, true))
					lightsOpen = !lightsOpen;

				if (ImGui::MenuItem("Material", " ", viewMaterial, true))
					viewMaterial = !viewMaterial;

				if (ImGui::MenuItem("Debug", " ", debug, true))
					debug = !debug;

				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}

		if (viewportOpen)
			Viewport(viewportOpen);
		if (lightsOpen)
			LightingSettings(lightsOpen);
		if (viewMaterial)
			MaterialView(viewMaterial);
		if (debug)
			Debug(debug);

		ImGui::End();
	}

	void EditorLayer::Viewport(bool& open)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_::ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGuiIO io = ImGui::GetIO();
		ImGuiWindowFlags flag = ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollbar;

		ImGui::Begin("Viewport", &open, flag);

		ImVec2 vPanelSize = ImGui::GetContentRegionAvail();
		ImVec2 vPanelPos = ImGui::GetCursorPos();

		m_ViewportSize = vPanelSize;
		m_ViewportPos.x = vPanelPos.x;
		m_ViewportPos.y = vPanelPos.y;

		uint64_t textureID = m_Framebuffer->GetTexID();
		ImGui::Image((void*)textureID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

		ImGui::End();
		ImGui::PopStyleVar();
	}

	void EditorLayer::LightingSettings(bool& open)
	{
		ImGui::Begin("Lighting Settings", &open);

		bool changedLights = false;
		static bool lightsOn = false;
		static float ambientStrength = 0.2f;

		if (ImGui::Checkbox("Lights On", &lightsOn))
			changedLights = true;

		if (ImGui::DragFloat("Ambient Light", &ambientStrength, Time::DeltaTime(), 0.0f, 1.0f))
		{
			ambientLight.x = ambientStrength;
			ambientLight.y = ambientStrength;
			ambientLight.z = ambientStrength;
			changedLights = true;
		}

		if (lightsOn)
		{
			ImGui::DragFloat3("Light Position", &light->Position[0], Time::DeltaTime());
			ImGui::DragFloat("Light Lineer", &light->Lineer, Time::DeltaTime() / 5.0f, 0.0f, 1.0f);
			ImGui::DragFloat("Light Quadradic", &light->Quadratic, Time::DeltaTime() / 5.0f, 0.0f, 2.0f);
		}
		ImGui::End();

		if (changedLights)
			Renderer::LightConfig(lightsOn, ambientLight);
	}

	void EditorLayer::MaterialView(bool& open)
	{
		static int selectionMode = 0;
		static ImGui::FileBrowser fileBrowser;

		ImGui::Begin("Material", &open);
		fileBrowser.SetTitle("Select Texture");
		fileBrowser.SetTypeFilters({ ".png", ".jpg", ".jpeg" });

		if (m_Diffuse == nullptr)
			m_Diffuse = new Texture("res/Textures/default.png");
		
		if (m_Specular == nullptr)
			m_Specular = new Texture("res/Textures/default.png");
		
		ImGui::Text("Diffuse Texture: ");
		if (ImGui::ImageButton((void*)m_Diffuse->GetID(), ImVec2{ 100, 100 }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 }))
		{
			fileBrowser.Open();
			selectionMode = 1;
		}
		
		ImGui::Text("Specular Texture: ");
		if (ImGui::ImageButton((void*)m_Specular->GetID(), ImVec2{ 100, 100 }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 }))
		{
			fileBrowser.Open();
			selectionMode = 2;
		}

		fileBrowser.Display();

		if (fileBrowser.HasSelected())
		{
			if (selectionMode == 1)
			{
				if(m_Diffuse != nullptr)
					delete m_Diffuse;
				m_Diffuse = new Texture(fileBrowser.GetSelected().string());
			}
			else if (selectionMode == 2)
			{
				if (m_Specular != nullptr)
					delete m_Specular;
				m_Specular = new Texture(fileBrowser.GetSelected().string());
			}

			if (mesh != nullptr)
			{
				mesh->Material_->DiffuseMap = m_Diffuse;
				mesh->Material_->SpecularMap = m_Specular;
			}
			fileBrowser.ClearSelected();
		}

		static float shininess = 1.0f;
		ImGui::Text("Shininnes: ");
		ImGui::SameLine();
		ImGui::SliderFloat(" ", &shininess, 0.0f, 1.0f);
		if (mesh != nullptr)
			mesh->Material_->Shininess = shininess;

		ImGui::End();
	}

	void EditorLayer::Debug(bool& open)
	{
		ImGui::Begin("Debug", &open);
		ImGui::Text("FPS: %.1f FPS (%.2f ms/frame) ", ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);
		ImGui::Text("Vertices Count: %d", RendererStats::vertices);
		ImGui::End();
	}

	void EditorLayer::OnDetach()
	{
		delete m_Controller;
		delete m_Scene;
	}
}
