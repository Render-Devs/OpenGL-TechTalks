#pragma once

class IRenderer
{
public:
	virtual ~IRenderer() {};
	virtual void Init() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void PostUpdate(float deltaTime) = 0;
	virtual void SetViewport(uint32_t width, uint32_t height) = 0;
};