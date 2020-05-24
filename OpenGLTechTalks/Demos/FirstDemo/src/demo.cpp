/*
Requirements:

	Couple of quads moving through screen via predefined (discussed) algorithm
	Each of couple using different drawing strategy (DrawArrays, DrawElements, BaseVertex, RestartPrimitives etc.)
	Each couple has a unique shader. (for ex. couple of 5 quads drawing as red).
	Other couples should use different shader strategies (subroutines, separate shader object)
	Possibility to look on each couple separately via pressed key (up to you what assign to your couple, use/create mapping doc with assigned feature to key.
	PostProcessing Effects using framebuffer (Gauasian blur, Grayscale, Negative, Gamma Correction)
*/

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Core.h"
#include "Basic.h"
#include "Shader.h"

#include <iostream>
#include <vector>
#include <map>
#include <cassert>
#include <string>


enum class DrawType
{
	DrawArrays,
	DrawElements,
	DrawArraysIndirect,
	DrawElementsIndirect,
	DrawArraysInstanced,
	DrawElemensInstanced,
	DrawArraysInstancedBaseInstance,
	DrawElementsInstancedBaseInstance,
	DrawMultiArrays,
	DrawMultiElements
};

enum class ShaderFeature
{
	Simple,
	Subroutines,
	SeparateShaderObjects,
	RestartingPrimitives,
	PostProcessing_Blur,
	PostProcessing_Grayscale,
	PostProcessing_Negative,
	PostProcessing_GammaCorrection
};

class ShaderLib
{
public:
	core::Shader* GetShader(GLuint shaderId)
	{
		if (shaderCollection.find(shaderId) != shaderCollection.end())
		{
			return shaderCollection.at(shaderId);
		}
		const std::string message = std::string("Shader with id: ") + std::to_string(shaderId) + std::string("not exist");
		throw std::runtime_error(message);
	}

	GLuint StoreShader(core::Shader* shader)
	{
		shaderCollection.insert(std::make_pair(shaderStoreIndex++, shader));
	}

	void DeleteShader(GLuint shaderId)
	{
		if (shaderCollection.find(shaderId) != shaderCollection.end())
		{
			delete shaderCollection.at(shaderId);
			shaderCollection.erase(shaderId);
			return;
		}
		const std::string message = std::string("Shader with id: ") + std::to_string(shaderId) + std::string("not exist");
		throw std::runtime_error(message);
	}

	void Clear()
	{
		for each (auto pair in shaderCollection)
		{
			if (pair.second != nullptr)
			{
				delete pair.second;
			}
		}
		shaderCollection.clear();
	}

	~ShaderLib()
	{
		Clear();
	}

private:
	GLuint shaderStoreIndex = 0;
	std::unordered_map<GLuint, core::Shader*> shaderCollection;
};

class FirstDemo final : public IRenderer
{
private:
	const uint32_t AMOUNT_OF_QUADS = 4;
	const std::vector<GLfloat> quadVerticies
	{
		-0.5f, -0.5f, 0.0f,
		-0.5f,	0.5f, 0.0f,
		 0.5f,	0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f
	};

	const std::vector<GLubyte> quadIndicies
	{
		0,1,2,0,2,3
	};

	GLuint vertexArray;
	GLuint vertexBuffer;
	GLuint elementBuffer;

	ShaderLib* shaderLib;

protected:
	void Init() override
	{
		shaderLib = new ShaderLib();
		glCreateBuffers(2, new GLuint[2]{ vertexBuffer, elementBuffer });
		glCreateVertexArrays(1, &vertexArray);

		glBindVertexArray(vertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, quadVerticies.size() * sizeof(GLfloat), quadVerticies.data(), GL_STATIC_DRAW);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, quadIndicies.size(), quadIndicies.data(), GL_STATIC_DRAW);
		
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), nullptr);
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Update(float deltaTime) override
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void PostUpdate(float) override
	{
	}

	void Dispose() override
	{
		glDeleteVertexArrays(1, &vertexArray);
		glDeleteBuffers(2, new GLuint[2]{ vertexBuffer, elementBuffer });
		delete shaderLib;
	}

	void SetViewport(uint32_t width, uint32_t height) override
	{
		glViewport(0, 0, width, height);
	}

private:
	//TODO: could be extended/ simplified (depends on your needs)
	void DrawQuadChunk(core::Shader* shader, DrawType drawType, ShaderFeature shaderFeature)
	{
		shader->SetActive(true);
		switch (shaderFeature)
		{
			case ShaderFeature::Simple:
			{
				break;
			}
			case ShaderFeature::Subroutines:
			{
				break;
			}
			case ShaderFeature::SeparateShaderObjects:
			{
				break;
			}
			case ShaderFeature::RestartingPrimitives:
			{
				break;
			}
			case ShaderFeature::PostProcessing_Blur:
			{
				break;
			}
			case ShaderFeature::PostProcessing_Grayscale:
			{
				break;
			}
			case ShaderFeature::PostProcessing_Negative:
			{
				break;
			}
			case ShaderFeature::PostProcessing_GammaCorrection:
			{
				break;
			}
		}
		glBindVertexArray(vertexArray);
		for (uint32_t index = 0; index < AMOUNT_OF_QUADS; index++)
		{
			DrawQuad(shader, drawType);
		}
	}

	void DrawQuad(core::Shader* shader, DrawType drawType)
	{
		//TODO: setup shader data here (if it should be changed per quad)
		switch (drawType)
		{
			case DrawType::DrawArrays:
			{
				break;
			}
			case DrawType::DrawArraysIndirect:
			{
				break;
			}
			case DrawType::DrawArraysInstanced:
			{
				break;
			}
			case DrawType::DrawArraysInstancedBaseInstance:
			{
				break;
			}
			case DrawType::DrawMultiArrays:
			{
				break;
			}
			case DrawType::DrawElements:
			{
				break;
			}
			case DrawType::DrawElementsIndirect:
			{
				break;
			}
			case DrawType::DrawElemensInstanced:
			{
				break;
			}
			case DrawType::DrawElementsInstancedBaseInstance:
			{
				break;
			}
			case DrawType::DrawMultiElements:
			{
				break;
			}
		}
	}
};

class DemoApp final : public Application
{
public:
	DemoApp(IRenderer* renderer, const WindowData& windowData) : Application(renderer, windowData) {}
};

Application* CreateApplication()
{
	return new DemoApp(new FirstDemo(), WindowData("FirstDemo"));
}