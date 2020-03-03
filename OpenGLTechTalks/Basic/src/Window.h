#pragma once
#include "GLFW\glfw3.h"
#include "Events\Event.h"
#include <string>
#include <functional>

struct WindowData
{
	std::string Title;
	uint32_t width, height;
	WindowData(const std::string& title = "OpenGL Tutorial", uint32_t width = 1920, uint32_t height = 1080) : 
		Title(title), width(width), height(height) {}
};

class IWindow
{
public:
	using EventCallback = std::function<void(Event&)>;

	virtual ~IWindow() {}
	virtual void OnUpdate() = 0;
	virtual uint32_t GetWidth() const = 0;
	virtual uint32_t GetHeight() const = 0;

	virtual void SetEventCallback(const EventCallback& callback) = 0;
	virtual void SetVSync(bool enabled) = 0;
	virtual bool IsVSync() const = 0;

	virtual void* GetNativeWindow() const = 0;
	virtual void Shutdown() = 0;

	static IWindow* Create(const WindowData& data = WindowData());

};