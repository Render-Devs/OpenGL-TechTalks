#pragma once
#include "Window.h"
#include "GraphicContext.h"

class OpenGLWindow : public IWindow
{
public:
	OpenGLWindow(const WindowData& data);
	virtual ~OpenGLWindow();

	void OnUpdate() override;

	inline unsigned int GetWidth() const override { return m_Data.Width; }
	inline unsigned int GetHeight() const override { return m_Data.Height; }
	inline void SetEventCallback(const EventCallback& callback) override { m_Data.EventCallback = callback; }
	void SetVSync(bool enabled) override;
	bool IsVSync() const override;
	virtual void* GetNativeWindow() const override { return m_Window; };
	virtual void Shutdown() override;

private:
	virtual void Init(const WindowData& props);

	GLFWwindow* m_Window;
	Scope<GraphicsContext> m_Context;

	struct WindowInternalData
	{
		std::string Title;
		uint32_t Width, Height;
		EventCallback EventCallback;
		bool VSync;
	};

	WindowInternalData m_Data;
};