#pragma once
#include "Renderer.h"
#include <obj_loader/obj_loader.h>
#include <glm/glm.hpp>
#include <GL/glew.h>

namespace Core
{
	struct Material
	{
		Texture* DiffuseMap;
		Texture* SpecularMap;
		float Shininess;

		Material()
		{
			DiffuseMap = new Texture("res/Textures/default.png");
			SpecularMap = new Texture("res/Textures/default.png");
			Shininess = 1.0f;
		}

		~Material()
		{
			delete DiffuseMap;
			delete SpecularMap;
		}

		Material(const std::string& diffusePath, const std::string& specularPath)
		{
			DiffuseMap = new Texture(diffusePath);
			SpecularMap = new Texture(specularPath);
			Shininess = 1.0f;
		}
	};

	struct VertexData
	{
	private:
		glm::vec3 pos;
		glm::vec2 texCoord;
		glm::vec3 normal;
	
	public:
		VertexData(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal)
		{
			this->pos = pos;
			this->texCoord = texCoord;
			this->normal = normal;
		}
	
		glm::vec3* GetPos() { return &pos; }
		glm::vec2* GetTexCoord() { return &texCoord; }
		glm::vec3* GetNormal() { return &normal; }
	};
	
	class Mesh
	{
	private:
		void CreateMesh(const IndexedModel& model);
		unsigned int m_VAO;
		unsigned int m_VAs[4];
		unsigned int m_IndicesCount = 0;
		unsigned int m_VertexCount = 0;
		void Draw();
		friend class Renderer;

	public:
		Material* Material_;
		glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };
		Mesh(VertexData* vertices, unsigned int numVertices, unsigned int indices[]);
	    Mesh(const std::string& modelPath);
		Mesh(const Mesh& mesh) = default;
		~Mesh();
		unsigned int GetVerticesCount() { return m_VertexCount; }
	};
}
