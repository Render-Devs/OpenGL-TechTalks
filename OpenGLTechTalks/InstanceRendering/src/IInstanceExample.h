#pragma once

class IInstanceExample
{
public:
	virtual void Init() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Dispose() = 0;
};