#pragma once
#include "Vinyl/Core/Base.h"
#include "Vinyl/Core/Log.h"
#include "Vinyl/Scene/Scene.h"
#include "Vinyl/Scene/Entity.h"

namespace Vinyl 
{
	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& scene);
		void SetContext(const Ref<Scene>& scene);
		void OnImGuiRender();
	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};
}