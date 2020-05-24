#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Basic.h"
#include "Shader.h"
#include "IInstanceExample.h"

class SimpleInstancing : public IInstanceExample
{
private:
	GLuint vertexBuffer, vertexArray;
	core::Shader* shader;
	glm::vec2 translations[100];
protected:
	void Init() override
	{
		shader = new core::Shader("simpleInstancing.vert", "simpleInstancing.frag");
		GLfloat q_verticies[] =
		{
			// positions     // colors
			-0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
			 0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
			-0.05f, -0.05f,  0.0f, 0.0f, 1.0f,

			-0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
			 0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
			 0.05f,  0.05f,  0.0f, 1.0f, 1.0f
		};

		int index = 0;
		float offset = 0.1f;
		for (int y = -10; y < 10; y += 2)
		{
			for (int x = -10; x < 10; x += 2)
			{
				glm::vec2 translation;
				translation.x = (float)x / 10.0f + offset;
				translation.y = (float)y / 10.0f + offset;
				translations[index++] = translation;
			}
		}

		glCreateVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);

		glCreateBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(q_verticies), q_verticies, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	}

	void Update(float deltaTime) override
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader->SetActive(true);

		for (unsigned int i = 0; i < 100; i++)
		{
			shader->setVec2(("offsets[" + std::to_string(i) + "]"), translations[i]);
		}

		glBindVertexArray(vertexArray);
		glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100);
	}


	void Dispose() override
	{
		delete shader;
		glDeleteVertexArrays(1, &vertexArray);
		glDeleteBuffers(1, &vertexBuffer);
	}

};