#pragma once
#include "Core.h"
#include "Texture.h"
#include "Shader.h"

namespace Core
{
	struct RendererStats
	{
		static unsigned int vertices;
	};

	class Framebuffer;
	class Mesh;
	struct Light;

	class Renderer
	{
	private:
		static glm::mat4 m_ViewProjection;

		static Light* m_Light;
		static glm::vec3 m_AmbientLight;
		static bool m_LightsOn;
	public:
		static void Awake();
		static void Clear();
		static void LightConfig(bool lightsOn, const glm::vec3& ambientValue);
		static void DrawLight(Light& light);
		static void Begin(const glm::mat4& vp);
		static void End();
		static void Begin(const glm::mat4& vp, Framebuffer& framebuffer);
		static void End(Framebuffer& framebuffer);
		static void DrawMesh(Mesh& mesh);
		static glm::mat4& ViewProjection() { return m_ViewProjection; }
	};
}