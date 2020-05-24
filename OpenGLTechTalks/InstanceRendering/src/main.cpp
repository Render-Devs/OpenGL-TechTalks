#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Basic.h"
#include "Shader.h"
#include "SimpleInstancing.h"
#include "InstancedArrays.h"

#include <iostream>

class InstanceRenderer final : public IRenderer
{
private:
	IInstanceExample* example;
public:
	InstanceRenderer()
	{
		std::cout << "Choose type of implementation: " << std::endl;
		std::cout << "1. Simple instance implementation." << std::endl;
		std::cout << "2. Instanced arrays implementation." << std::endl;
		std::cout << "Your choose (1 .. 4): ";
		int answer;
		std::cin >> answer;

		switch (answer)
		{
		case 1:
			example = new SimpleInstancing();
			break;
		case 2:
			example = new InstancedArrays();
			break;
		}
	}

	void Init() override
	{
		example->Init();
	}

	void Update(float deltaTime) override
	{
		example->Update(deltaTime);
	}

	void PostUpdate(float) override
	{

	}

	void Dispose() override
	{
		example->Dispose();
		delete example;
	}

	void SetViewport(uint32_t width, uint32_t height) override
	{
		glViewport(0, 0, width, height);
	}
};

class App : public Application
{
public:
	App(IRenderer* renderer, const WindowData& windowData) : Application(renderer, windowData)
	{}

};

Application* CreateApplication()
{
	return new App(new InstanceRenderer(), WindowData("Instance Rendering", 800, 600));
}