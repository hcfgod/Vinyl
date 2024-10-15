#pragma once

#include "RenderCommand.h"
#include "Vinyl/Rendering/Shader.h"
#include "Vinyl/Rendering/Camera/OrthographicCamera.h"

namespace Vinyl
{
	class Renderer
	{
	public:
		static void BeginScene(OrthographicCamera& camera); // TODO: take in all the scene paramaters we need
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);

		static inline RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
		static inline void SetAPI(RendererAPI::API api) { RendererAPI::SetAPI(api); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}