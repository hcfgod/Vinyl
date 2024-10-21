#pragma once

#include "Vinyl/Rendering/Camera/OrthographicCamera.h"
#include "Vinyl/Rendering/Texture.h"
#include "Vinyl/Rendering/SubTexture2D.h"

namespace Vinyl
{
	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		static void Flush();

        // Primitives
        static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

        static void DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, const glm::vec4& tintColor = glm::vec4(1.0f), float tilingFactor = 1.0f);
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tintColor = glm::vec4(1.0f), float tilingFactor = 1.0f);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tintColor = glm::vec4(1.0f), float tilingFactor = 1.0f);

        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<SubTexture2D>& subTexture, const glm::vec4& tintColor = glm::vec4(1.0f), float tilingFactor = 1.0f);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<SubTexture2D>& subTexture, const glm::vec4& tintColor = glm::vec4(1.0f), float tilingFactor = 1.0f);
        static void DrawQuad(const glm::mat4& transform, const Ref<SubTexture2D>& subTexture, const glm::vec4& tintColor = glm::vec4(1.0f), float tilingFactor = 1.0f);

        static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor);
        static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor);

        static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
        static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
        static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const glm::vec4& tintColor = glm::vec4(1.0f), float tilingFactor = 1.0f);
        static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const glm::vec4& tintColor = glm::vec4(1.0f), float tilingFactor = 1.0f);

        static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<SubTexture2D>& subTexture, const glm::vec4& tintColor = glm::vec4(1.0f), float tilingFactor = 1.0f);
        static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<SubTexture2D>& subTexture, const glm::vec4& tintColor = glm::vec4(1.0f), float tilingFactor = 1.0f);

		static void DrawRotatedQuad(const glm::mat4& transform, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, const glm::vec4& tintColor = glm::vec4(1.0f), float tilingFactor = 1.0f);

		// Statistics
		struct Statistics
		{
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;

			uint32_t GetTotalVertexCount() { return QuadCount * 4; }
			uint32_t GetTotalIndexCount() { return QuadCount * 6; }
		};

		static void ResetStatistics();
		static Statistics& GetStatistics();
	private:
		static void FlushAndReset();

		static void DrawQuadInternal(const glm::mat4& transform, const glm::vec4& color, const Ref<Texture2D>& texture = nullptr, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
	};
}