#include "vlpch.h"

#include "Buffer.h"

#include "Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Vinyl
{
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: VL_CORE_ASSERT(false, "Currently we do not support RendererAPI::None. Please choose a different Rendering API."); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		}

		VL_CORE_ASSERT(false, "Unknown rendererAPI!"); 
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: VL_CORE_ASSERT(false, "Currently we do not support RendererAPI::None. Please choose a different Rendering API."); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLIndexBuffer>(indices, count);
		}

		VL_CORE_ASSERT(false, "Unknown rendererAPI!");
		return nullptr;
	}
}