#include "Basic.h"

class Renderer : public IRenderer
{
	// Inherited via IRenderer
	virtual void Init() override
	{
	}
	virtual void Update(float deltaTime) override
	{
	}
	virtual void PostUpdate(float deltaTime) override
	{
	}
	virtual void SetViewport(uint32_t width, uint32_t height) override
	{
	}
	virtual void Dispose() override
	{

	}
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