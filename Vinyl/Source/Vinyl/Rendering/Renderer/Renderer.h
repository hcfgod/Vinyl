#pragma once

#include "RenderCommand.h"

namespace Vinyl
{
	class Renderer
	{
	public:
		static void BeginScene(); // TODO: take in all the scene paramaters we need
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		static inline RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
		static inline void SetAPI(RendererAPI::API api) { RendererAPI::SetAPI(api); }
	};
}