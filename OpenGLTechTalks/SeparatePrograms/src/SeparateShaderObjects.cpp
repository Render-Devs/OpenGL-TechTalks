#include "Basic.h"

static bool counter;
static float CalculatedTime;
static void UpdateCounter(float deltaTime)
{
	CalculatedTime += deltaTime;
	if (CalculatedTime > 1.0f)
	{
		CalculatedTime = 0;
		counter = !counter;
	}
}

class Renderer : public IRenderer
{
public:
	virtual void Init() override
	{
		sepVertex = new core::Shader("vertexOnly.vert", GL_VERTEX_SHADER);
		sepFrag1 = new core::Shader("fragOnlyVarOne.frag", GL_FRAGMENT_SHADER);
		sepFrag2 = new core::Shader("fragOnlyVarTwo.frag", GL_FRAGMENT_SHADER);
	
		float vertices[] =
		{
			0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
			0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
		};
		glCreateVertexArrays(1, &vertexArray);
		glCreateBuffers(1, &vertexBuffer);

		glBindVertexArray(vertexArray);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);

		glGenProgramPipelines(2, programPipes);

		glUseProgramStages(programPipes[0], GL_VERTEX_SHADER_BIT, sepVertex->getID());
		glUseProgramStages(programPipes[0], GL_FRAGMENT_SHADER_BIT, sepFrag1->getID());
		
		glUseProgramStages(programPipes[1], GL_VERTEX_SHADER_BIT, sepVertex->getID());
		glUseProgramStages(programPipes[1], GL_FRAGMENT_SHADER_BIT, sepFrag2->getID());
	}

	virtual void Update(float deltaTime) override
	{
		UpdateCounter(deltaTime);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(0);

		glBindProgramPipeline(counter ? programPipes[0] : programPipes[1]);

		glBindVertexArray(vertexArray);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glFlush();
	}

	virtual void PostUpdate(float deltaTime) override
	{

	}

	virtual void SetViewport(uint32_t width, uint32_t height) override
	{
		glViewport(0, 0, width, height);
	}

	virtual void Dispose() override
	{
		glDeleteProgramPipelines(2, programPipes);

		delete sepVertex;
		delete sepFrag1;
		delete sepFrag2;

		glDeleteVertexArrays(1, &vertexArray);
		glDeleteBuffers(1, &vertexBuffer);
	}

private:
	GLuint vertexArray, vertexBuffer;
	core::Shader* sepVertex;
	core::Shader* sepFrag1;
	core::Shader* sepFrag2;

	GLuint programPipes[2];
};

class App : public Application
{
public:
	App(IRenderer* render) : Application(render)
	{

	}
};

Application* CreateApplication()
{
	return new App(new Renderer());
}