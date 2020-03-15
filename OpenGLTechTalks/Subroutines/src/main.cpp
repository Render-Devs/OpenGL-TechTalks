#include <Basic.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	Shader(const char* vPath, const char* fPath)
	{
		std::string vertexCode;
		std::string fragmentCode;
		std::string geometryCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	
		try
		{
			vShaderFile.open(vPath);
			fShaderFile.open(fPath);

			std::stringstream vStream, fStream;

			vStream << vShaderFile.rdbuf();
			fStream << fShaderFile.rdbuf();

			vShaderFile.close();
			fShaderFile.close();

			vertexCode = vStream.str();
			fragmentCode = fStream.str();

		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}

		const char* vCodeStr = vertexCode.c_str();
		const char* fCodeStr = fragmentCode.c_str();

		unsigned int vertex, fragment;

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vCodeStr, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fCodeStr, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");

		RendererId = glCreateProgram();
		glAttachShader(RendererId, vertex);
		glAttachShader(RendererId, fragment);

		glLinkProgram(RendererId);
		checkCompileErrors(RendererId, "PROGRAM");


		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	void Use()
	{
		glUseProgram(RendererId);
	}

	unsigned int GetId() const
	{
		return RendererId;
	}

private:
	unsigned int RendererId;

	void checkCompileErrors(unsigned int shader, std::string type)
	{
		int success;
		char infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}
};

struct Subroutine
{
	GLuint sub_index;
	std::string sub_name;
};

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
	// Inherited via IRenderer
	virtual void Init() override
	{
		vanillaShader = new Shader("vertexShaderVanilla.vert", "fragmentShaderVanilla.frag");
		subroutinedShader = new Shader("vertexShaderSubroutined.vert", "fragmentShaderSubroutined.frag");
		
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
	}

	virtual void Update(float deltaTime) override
	{
		UpdateCounter(deltaTime);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(0);
		

		GLuint colorSelector = glGetSubroutineUniformLocation(subroutinedShader->GetId(), GL_FRAGMENT_SHADER, "newGradientColor");
		GLuint redIndex = glGetSubroutineIndex(subroutinedShader->GetId(), GL_FRAGMENT_SHADER, "redColor");
		GLuint blueIndex = glGetSubroutineIndex(subroutinedShader->GetId(), GL_FRAGMENT_SHADER, "blueColor");

		GLsizei size;
		glGetProgramStageiv(subroutinedShader->GetId(), GL_FRAGMENT_SHADER, GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS, &size);
		GLuint* indicies = new GLuint[size];
		indicies[colorSelector] = counter ? redIndex : blueIndex;

		subroutinedShader->Use();
		glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, size, indicies);

		delete[] indicies;

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
		delete vanillaShader;

		glDeleteVertexArrays(1, &vertexArray);
		glDeleteBuffers(1, &vertexBuffer);
	}

private:
	unsigned int vertexArray, vertexBuffer;
	Shader* vanillaShader;
	Shader* subroutinedShader;
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