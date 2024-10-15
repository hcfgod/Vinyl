#include "vlpch.h"

#include "RenderCommand.h"

#include "Platform/OpenGL/Renderer/OpenGLRendererAPI.h"

namespace Vinyl
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}