#pragma once

#include "Vinyl/Rendering/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Vinyl
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}