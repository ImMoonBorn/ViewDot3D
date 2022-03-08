#pragma once
#include "Renderer.h"

namespace Core
{
	struct Light
	{
	private:
		unsigned int vbo;
		unsigned int vao;
		unsigned int ibo;
		int strideLength = 3;

		float vertices[48] =
		{
			-0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f,

			 0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,

			-0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,

			-0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f
		};

		unsigned int indices[36] =
		{
			0, 1, 2, 0, 2, 3,
			4, 1, 2, 4, 2, 7,
			4, 5, 7, 5, 6, 7,
			0, 3, 5, 3, 5, 6,
			8, 9, 10, 8, 10, 11,
			12, 13, 14, 12, 14, 15
		};

		void Awake()
		{
			glGenVertexArrays(1, &vao);
			glGenBuffers(1, &vbo);

			glBindVertexArray(vao);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, strideLength * sizeof(float), 0);

			glGenBuffers(1, &ibo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		}

	public:
		enum class LightType 
		{
			Point,
			Directional
		};

		LightType lightType = LightType::Point;
		glm::vec3 Position = {0.0f, 0.0f, 0.0f};
		Shader* shader = new Shader("res/Shaders/Light.shader");
		float Lineer = 0.9f;
		float Quadratic = 0.032f;
		Light() { Awake(); }
		
		void Draw()
		{
			glBindVertexArray(vao);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
			glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
		}
	};
}