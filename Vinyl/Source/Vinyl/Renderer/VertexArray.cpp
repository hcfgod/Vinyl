#include "vlpch.h"

#include "VertexArray.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Vinyl
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None: VL_CORE_ASSERT(false, "Currently we do not support RendererAPI::None. Please choose a different Rendering API."); return nullptr;
			case RendererAPI::OpenGL: return new OpenGLVertexArray();
		}

		VL_CORE_ASSERT(false, "Unknown rendererAPI!");
		return nullptr;
	}
}