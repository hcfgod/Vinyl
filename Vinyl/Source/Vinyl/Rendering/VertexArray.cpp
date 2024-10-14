#include "vlpch.h"

#include "VertexArray.h"
#include "Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Vinyl
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: VL_CORE_ASSERT(false, "Currently we do not support RendererAPI::None. Please choose a different Rendering API."); return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		}

		VL_CORE_ASSERT(false, "Unknown rendererAPI!");
		return nullptr;
	}
}