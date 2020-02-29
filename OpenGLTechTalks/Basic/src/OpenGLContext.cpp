#include "OpenGLContext.h"

OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle)
{

}

void OpenGLContext::Init()
{
	glfwMakeContextCurrent(m_WindowHandle);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

void OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(m_WindowHandle);
}
