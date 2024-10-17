#include "vlpch.h"

#include "RenderCommand.h"

#include "Platform/OpenGL/Renderer/OpenGLRendererAPI.h"

namespace Vinyl
{
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}