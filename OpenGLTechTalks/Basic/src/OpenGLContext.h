#pragma once
#include "GraphicContext.h"
#include "glad\glad.h"
#include <GLFW\glfw3.h>

class OpenGLContext : public GraphicsContext
{
public:
	OpenGLContext(GLFWwindow* windowHandle);
	virtual void Init() override;
	virtual void SwapBuffers() override;

private:
	GLFWwindow* m_WindowHandle;
};