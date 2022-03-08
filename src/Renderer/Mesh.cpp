#include "pch.h"
#include "mesh.h"

namespace Core
{
	Mesh::Mesh(const std::string& fileName)
	{
	    CreateMesh(OBJModel(fileName).ToIndexedModel());
	}
	
	void Mesh::CreateMesh(const IndexedModel& model)
	{
		m_IndicesCount = (unsigned int) model.indices.size();
		m_VertexCount = model.vertexCount;

		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);
		glGenBuffers(4, m_VAs);
		
		glBindBuffer(GL_ARRAY_BUFFER, m_VAs[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(model.positions[0]) * model.positions.size(), &model.positions[0], GL_STATIC_DRAW);
	    glEnableVertexAttribArray(0);
	    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
		glBindBuffer(GL_ARRAY_BUFFER, m_VAs[1]);
	    glBufferData(GL_ARRAY_BUFFER, sizeof(model.texCoords[0]) * model.texCoords.size(), &model.texCoords[0], GL_STATIC_DRAW);
	    glEnableVertexAttribArray(1);
	    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	
		glBindBuffer(GL_ARRAY_BUFFER, m_VAs[2]);
	    glBufferData(GL_ARRAY_BUFFER, sizeof(model.normals[0]) * model.normals.size(), &model.normals[0], GL_STATIC_DRAW);
	    glEnableVertexAttribArray(2);
	    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VAs[3]);
	    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(model.indices[0]) * model.indices.size(), &model.indices[0], GL_STATIC_DRAW);
	
		glBindVertexArray(0);

		Material_ = new Material();
	}
	
	Mesh::Mesh(VertexData* vertices, unsigned int numVertices, unsigned int indices[])
	{
	    IndexedModel model;
		for(unsigned int i = 0; i < numVertices; i++)
		{
			model.positions.push_back(*vertices[i].GetPos());
			model.texCoords.push_back(*vertices[i].GetTexCoord());
			model.normals.push_back(*vertices[i].GetNormal());
		}
		
		for(unsigned int i = 0; i < sizeof(indices); i++)
	        model.indices.push_back(indices[i]);
	
	    CreateMesh(model);
	}
	
	void Mesh::Draw()
	{
		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, m_IndicesCount, GL_UNSIGNED_INT, 0);
	}
	
	Mesh::~Mesh()
	{
		glDeleteBuffers(4, m_VAs);
		glDeleteVertexArrays(1, &m_VAO);
		delete Material_;
	}
}
