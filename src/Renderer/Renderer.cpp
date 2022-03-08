#include "pch.h"
#include "Renderer.h"
#include "Frambuffer.h"
#include "Utils/Camera.h"
#include "Mesh.h"
#include "Light.h"

namespace Core
{
	Light* Renderer::m_Light;
	glm::mat4 Renderer::m_ViewProjection;
	glm::vec3 Renderer::m_AmbientLight; 
	bool Renderer::m_LightsOn = false;

	Shader* shader;
	Shader* shaderNL;
	unsigned int RendererStats::vertices;

	void Renderer::Awake()
	{
		m_ViewProjection = glm::mat4(1.0f);
		shader = new Shader("res/Shaders/Default.shader");
		shaderNL = new Shader("res/Shaders/DefaultNL.shader");
		DebugSys("Renderer Initialized");
	}

	void Renderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		RendererStats::vertices = 0;
	}

	void Renderer::LightConfig(bool lightsOn, const glm::vec3& ambientValue)
	{
		m_LightsOn = lightsOn;
		m_AmbientLight = ambientValue;
	}

	void Renderer::Begin(const glm::mat4& vp)
	{
		m_ViewProjection = vp;
	}
	
	void Renderer::Begin(const glm::mat4& vp, Framebuffer& framebuffer)
	{
		m_ViewProjection = vp;
		framebuffer.Bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::End()
	{
	}

	void Renderer::End(Framebuffer& framebuffer)
	{
		framebuffer.Unbind();
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::DrawLight(Light& light)
	{
		if (!m_LightsOn)
			return;
		m_Light = &light;
		Shader& lightShader = *light.shader;
		lightShader.Bind();
		lightShader.SetUniformMat4("u_VP", m_ViewProjection);
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), light.Position);
		transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.5f));
		lightShader.SetUniformMat4("u_M", transform);
		light.Draw();
	}

	void Renderer::DrawMesh(Mesh& mesh)
	{
		if (m_LightsOn)
		{
			shader->Bind();
			shader->SetUniformMat4("u_VP", m_ViewProjection);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), mesh.Position);
			transform = glm::scale(transform, mesh.Scale);
			shader->SetUniformMat4("u_M", transform);
			shader->SetUniformVec3("u_CameraPos", Utils::Camera::CamPosition());
			shader->SetUniform1i("material.diffuse", 0);
			shader->SetUniform1i("material.specular", 1);
			shader->SetUniform1f("material.shininess", mesh.Material_->Shininess);
			shader->SetUniformVec3("light.position", m_Light->Position);
			shader->SetUniformVec3("light.ambient", m_AmbientLight);
			shader->SetUniformVec3("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
			shader->SetUniformVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
			shader->SetUniform1f("light.constant", 1.0f);
			shader->SetUniform1f("light.lineer", m_Light->Lineer);
			shader->SetUniform1f("light.quadratic", m_Light->Quadratic);
		}
		else
		{
			shaderNL->Bind();
			shaderNL->SetUniformMat4("u_VP", m_ViewProjection);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), mesh.Position);
			transform = glm::scale(transform, mesh.Scale);
			shaderNL->SetUniformMat4("u_M", transform);
			shaderNL->SetUniformVec3("u_CameraPos", Utils::Camera::CamPosition());
			shaderNL->SetUniform1i("material.diffuse", 0);
			shaderNL->SetUniform1i("material.specular", 1);
			shaderNL->SetUniform1f("material.shininess", 0.0f);
			shaderNL->SetUniformVec3("ambient", m_AmbientLight);
		}
		mesh.Material_->DiffuseMap->Bind();
		mesh.Material_->SpecularMap->Bind(1);
		mesh.Draw();
		RendererStats::vertices += mesh.GetVerticesCount();
	};
}
