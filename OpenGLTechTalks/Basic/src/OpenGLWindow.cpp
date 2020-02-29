#include "OpenGLWindow.h"
#include "OpenGLContext.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

static bool s_GLFWInitialized = false;

IWindow* IWindow::Create(const WindowData& data)
{
	return new OpenGLWindow(data);
}

OpenGLWindow::OpenGLWindow(const WindowData& data)
{
	Init(data);
}

OpenGLWindow::~OpenGLWindow()
{
	Shutdown();
}

void OpenGLWindow::Init(const WindowData& data)
{
	m_Data.Title = data.Title;
	m_Data.Width = data.width;
	m_Data.Height = data.height;

	if (!s_GLFWInitialized)
	{
		int success = glfwInit();
		if (success)
		{
			s_GLFWInitialized = true;
		}
		else
		{
			return;
		}
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	m_Window = glfwCreateWindow(data.width, data.height, m_Data.Title.c_str(), nullptr, nullptr);
	m_Context = CreateScope<OpenGLContext>(m_Window);
	m_Context->Init();
	glfwSetWindowUserPointer(m_Window, &m_Data);
	SetVSync(true);

	glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowInternalData& data = *(WindowInternalData*)glfwGetWindowUserPointer(window);

			data.Width = width;
			data.Height = height;
			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});
	glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
		WindowInternalData& data = *(WindowInternalData*)glfwGetWindowUserPointer(window);
		WindowCloseEvent event;
		data.EventCallback(event);
		});

	glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowInternalData& data = *(WindowInternalData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				KeyPressedEvent event(key, 0);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent event(key);
				data.EventCallback(event);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent event(key, 1);
				data.EventCallback(event);
				break;
			}
			}
		});
	glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
		{
			WindowInternalData& data = *(WindowInternalData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(keycode);
			data.EventCallback(event);
		});

	glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowInternalData& data = *(WindowInternalData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event(button);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(button);
				data.EventCallback(event);
				break;
			}
			}
		});

	glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double x, double y)
		{
			WindowInternalData& data = *(WindowInternalData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event((float)x, (float)y);
			data.EventCallback(event);
		});

	glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x, double y)
		{
			WindowInternalData& data = *(WindowInternalData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event((float)x, (float)y);
			data.EventCallback(event);
		});
}

void OpenGLWindow::Shutdown()
{
	glfwDestroyWindow(m_Window);
}

void OpenGLWindow::OnUpdate()
{
	glfwPollEvents();
	m_Context->SwapBuffers();
}

void OpenGLWindow::SetVSync(bool enabled)
{
	if (enabled)
	{
		glfwSwapInterval(1);
	}
	else
	{
		glfwSwapInterval(0);
	}
	m_Data.VSync = enabled;
}

bool OpenGLWindow::IsVSync() const
{
	return m_Data.VSync;
}