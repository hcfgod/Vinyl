#include "vlpch.h"

#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Vinyl
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None: VL_CORE_ASSERT(false, "Currently we do not support RendererAPI::None. Please choose a different Rendering API."); return nullptr;
			case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		}

		VL_CORE_ASSERT(false, "Unknown rendererAPI!"); 
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None: VL_CORE_ASSERT(false, "Currently we do not support RendererAPI::None. Please choose a different Rendering API."); return nullptr;
			case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, count);
		}

		VL_CORE_ASSERT(false, "Unknown rendererAPI!");
		return nullptr;
	}
}