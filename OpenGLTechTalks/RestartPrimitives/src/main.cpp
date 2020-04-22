#include <glad\glad.h>
#include "Basic.h"
#include <cmath>

#define USE_FIXED_INDEX 0

class RestartPrimitivesRenderer final : public IRenderer
{

private:
	GLuint vertexBuffer, elementBuffer, vertexArray;
	core::Shader* shader;
	GLsizei indiciesAmount;
protected:
	void Init() override
	{

		shader = new core::Shader("rpV.vert","rpF.frag");


		static const GLfloat cube_Pos[] =
		{
			-0.5f,  0.0f,  0.0f, 1.0f,
			-0.3f, -0.2f,  0.0f, 1.0f,
			-0.4f,  0.1f,  0.0f, 1.0f,
			-0.2f,  0.5f,  0.0f, 1.0f,
			 0.0f,  0.5f,  0.0f, 1.0f,
			 0.0f, -0.5f,  0.0f, 1.0f,
			 0.8f,  0.5f,  0.0f, 1.0f,
			 0.6f, -0.5f,  0.0f, 1.0f,
		};

		static const GLfloat cube_colors[] =
		{
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 1.0f, 1.0f,
			0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f, 1.0f,
			0.5f, 0.5f, 0.5f, 1.0f,
		};

		static const GLushort cube_indices[] =
		{
			0, 2, 1, 0xFFFF, 1, 4, 3, 0,
			0xFFFF,
			6, 7, 5, 0xFFFF, 5, 4, 7, 0xFFFF
		};

		indiciesAmount = sizeof(cube_indices) / sizeof(cube_indices[0]);

		glGenBuffers(1, &elementBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);

		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cube_Pos) + sizeof(cube_colors), NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(cube_Pos), cube_Pos);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(cube_Pos), sizeof(cube_colors), cube_colors);

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)sizeof(cube_Pos));
	
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
	
	}

	void Update(float deltaTime) override
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader->SetActive(true);

		glBindVertexArray(vertexArray);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);

#if USE_FIXED_INDEX
		glEnable(GL_PRIMITIVE_RESTART_FIXED_INDEX);
		glDrawElements(GL_TRIANGLE_STRIP, indiciesAmount, GL_UNSIGNED_SHORT, NULL);
		glDisable(GL_PRIMITIVE_RESTART_FIXED_INDEX);
#else
		glEnable(GL_PRIMITIVE_RESTART_INDEX);
		glPrimitiveRestartIndex(0xFFFF);
		glDrawElements(GL_TRIANGLE_STRIP, indiciesAmount, GL_UNSIGNED_SHORT, NULL);
		glDisable(GL_PRIMITIVE_RESTART_INDEX);
#endif
	}

	void PostUpdate(float) override
	{
	}

	void Dispose() override
	{
		glDeleteVertexArrays(1, &vertexArray);
		glDeleteBuffers(1, &vertexBuffer);
		glDeleteBuffers(1, &elementBuffer);
		delete shader;
	}

	void SetViewport(uint32_t width, uint32_t height) override
	{
		glViewport(0, 0, width, height);
	}
};

class RestartPrimitivesApp : public Application
{
public:
	RestartPrimitivesApp(IRenderer* render, const WindowData& windowData) : Application(render, windowData)
	{

	}
};

Application* CreateApplication()
{
	return new RestartPrimitivesApp(new RestartPrimitivesRenderer(), WindowData("glRestartPromitives", 800, 600));
}