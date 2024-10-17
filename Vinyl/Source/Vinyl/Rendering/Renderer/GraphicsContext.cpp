#include "vlpch.h"
#include "Vinyl/Rendering/Renderer/GraphicsContext.h"
#include "Vinyl/Rendering/Renderer/Renderer.h"
#include "Platform/OpenGL/Renderer/OpenGLContext.h"

namespace Vinyl 
{
	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    VL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}
		VL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}