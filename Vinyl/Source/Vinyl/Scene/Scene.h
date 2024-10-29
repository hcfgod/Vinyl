#pragma once

#include "Vinyl/Asset/Asset.h"
#include "Vinyl/Core/Timestep.h"
#include "Vinyl/Core/UUID.h"
#include "Vinyl/Rendering/Camera/EditorCamera.h"

#include <entt.hpp>

class b2World;

namespace Vinyl
{
	class Entity;

	class Scene : public Asset
	{
	public:
		Scene();
		~Scene();

		static Ref<Scene> Copy(Ref<Scene> other);
		virtual AssetType GetType() const { return AssetType::Scene; }

		Entity CreateEntity(const std::string& name = std::string());
		Entity CreateEntityWithUUID(UUID uuid, const std::string& name = std::string());
		void DestroyEntity(Entity entity);

		void OnRuntimeStart();
		void OnRuntimeStop();

		void OnSimulationStart();
		void OnSimulationStop();

		void Step(int frames = 1);

		void OnUpdateRuntime(TimeStep timestep);
		void OnUpdateSimulation(TimeStep timestep, EditorCamera& camera);
		void OnUpdateEditor(TimeStep timestep, EditorCamera& camera);
		void OnViewportResize(uint32_t width, uint32_t height);

		Entity DuplicateEntity(Entity entity);
		Entity FindEntityByName(std::string_view name);

		Entity GetMainCameraEntity();
		Entity GetEntityByUUID(UUID entityID);

		bool IsRunning() const { return m_IsRunning; }

		bool IsPaused() const { return m_IsPaused; }
		void SetPaused(bool paused) { m_IsPaused = paused; }

		template<typename... Components>
		auto GetAllEntitiesWith()
		{
			return m_Registry.view<Components...>();
		}
	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);

		void OnPhysics2DStart();
		void OnPhysics2DStop();

		float CalculateDistanceToCamera(const glm::vec3& entityPosition, const glm::vec3& cameraPosition) const;

		void RenderEntitiesPass(const glm::vec3& cameraPosition, Camera& camera, const glm::mat4& cameraTransform);

		void RenderScene(EditorCamera& camera);

	private:
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

		bool m_IsRunning = false;
		bool m_IsPaused = false;

		int m_StepFrames = 0;

		b2World* m_PhysicsWorld = nullptr;

		std::unordered_map<UUID, entt::entity> m_EntityMap;

		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchyPanel;
	};
}