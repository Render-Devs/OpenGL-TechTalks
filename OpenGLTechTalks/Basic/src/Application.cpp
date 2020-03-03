#include "Application.h"

Application* Application::s_Instance = nullptr;

Application::Application(IRenderer* renderer)
{
	s_Instance = this;
	m_Window = Scope<IWindow>(IWindow::Create());
	m_Window->SetEventCallback(BIND_EVENT(Application::OnEvent));
	m_Renderer = Scope<IRenderer>(renderer);
	m_Renderer->Init();
}

void Application::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT(Application::OnWindowClosed));
	dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT(Application::OnWindowResized));
}

bool Application::OnWindowClosed(WindowCloseEvent& e)
{
	m_Running = false;
	return true;
}

bool Application::OnWindowResized(WindowResizeEvent& e)
{
	m_Minimized = e.GetWidth() == 0 || e.GetHeight() == 0;
	m_Renderer->SetViewport(e.GetWidth(), e.GetHeight());
	return true;
}

void Application::Run()
{
	while (m_Running)
	{
		float time = (float)glfwGetTime();
		Timestep timestep = Timestep(time, time - m_LastFrameTime);
		m_LastFrameTime = time;

		if (!m_Minimized)
		{
			m_Renderer->Update(timestep);
			m_Renderer->PostUpdate(timestep);
		}

		m_Window->OnUpdate();
	}

	m_Renderer->Dispose();
	m_Window->Shutdown();
}