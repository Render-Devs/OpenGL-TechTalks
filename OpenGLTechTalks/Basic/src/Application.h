#pragma once
#include "Core.h"
#include "Timestep.h"
#include "Window.h"
#include "Events\Event.h"
#include "Events\ApplicationEvent.h"
#include "Events\KeyEvent.h"
#include "Events\MouseEvent.h"
#include "IRenderer.h"

class Application
{
public:
	Application(IRenderer* renderer, const WindowData& windowData);
	Application(IRenderer* renderer) : Application(renderer, WindowData()){}
	virtual ~Application() = default;
	void Run();
	void OnEvent(Event & e);
	inline IWindow& GetWindow() { return *m_Window; }
	inline static Application& Get() { return *s_Instance; }
private:
	bool OnWindowClosed(WindowCloseEvent & e);
	bool OnWindowResized(WindowResizeEvent & e);
private:
	Scope<IRenderer> m_Renderer;
	Scope<IWindow> m_Window;
	bool m_Running = true;
	bool m_Minimized = false;
	float m_LastFrameTime = 0.0f;
	static Application* s_Instance;
};

Application* CreateApplication();