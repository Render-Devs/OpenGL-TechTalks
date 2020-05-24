#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Basic.h"
#include "Shader.h"
#include "IInstanceExample.h"

class InstancedArrays : public IInstanceExample
{
private:
	GLuint vertexBuffer, instanceDataBuffer, vertexArray;
	core::Shader* shader;
	glm::vec2 translations[100];
protected:
	void Init() override
	{
		shader = new core::Shader("instancedArrays.vert", "instancedArrays.frag");
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

		/*GLushort q_elements[] =
		{
			0, 1, 2,
			0, 2, 3,
		};*/

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

		glCreateBuffers(1, &instanceDataBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, instanceDataBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 100, &translations[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);


		/*glCreateBuffers(1, &elementBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(q_elements), q_elements, GL_STATIC_DRAW);
		*/
		glCreateVertexArrays(1, &vertexArray);
		glCreateBuffers(1, &vertexBuffer);

		glBindVertexArray(vertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(q_verticies), q_verticies, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, instanceDataBuffer);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glVertexAttribDivisor(2, 1);
	}

	void Update(float deltaTime) override
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader->SetActive(true);
		glBindVertexArray(vertexArray);
		glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100);
	}


	void Dispose() override
	{
		delete shader;
		glDeleteVertexArrays(1, &vertexArray);
		glDeleteBuffers(1, &vertexBuffer);
		glDeleteBuffers(1, &instanceDataBuffer);
	}

};