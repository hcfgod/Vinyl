#pragma once

#include "Vinyl/Core/Timestep.h"
#include "Vinyl/Rendering/Camera/EditorCamera.h"
#include <entt.hpp>

namespace Vinyl
{
	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();
		Entity CreateEntity(const std::string& name = std::string());
		void DestroyEntity(Entity entity);

		void OnRuntimeUpdate(TimeStep timestep);
		void OnEditorUpdate(TimeStep timestep, EditorCamera& camera);
		void OnViewportResize(uint32_t width, uint32_t height);

		Entity GetMainCameraEntity();
	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);
	private:
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchyPanel;
	};
}