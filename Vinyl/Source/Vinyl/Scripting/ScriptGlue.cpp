#include "vlpch.h"

#include "Vinyl/Scripting/ScriptGlue.h"
#include "Vinyl/Scripting/ScriptEngine.h"

#include "Vinyl/Scene/Scene.h"
#include "Vinyl/Scene/Entity.h"

#include "Vinyl/Core/UUID.h"

#include "Vinyl/Core/Input/Input.h"
#include "Vinyl/Core/Input/KeyCodes.h"
#include "Vinyl/Core/Input/MouseButtons.h"

#include <mono/metadata/object.h>
#include <mono/metadata/reflection.h>

#include <box2d/b2_body.h>

#define VL_ADD_INTERNAL_CALL(Name) mono_add_internal_call("Vinyl.InternalCalls::"#Name, Name)

namespace Vinyl
{
	static std::unordered_map<MonoType*, std::function<bool(Entity)>> s_EntityHasComponentFuncs;

	static MonoObject* GetScriptInstance(UUID entityID)
	{
		return ScriptEngine::GetManagedInstance(entityID);
	}

	#pragma region Entity

	static bool Entity_HasComponent(UUID entityID, MonoReflectionType* componentType)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		VL_CORE_ASSERT(scene, "ScriptEngine Scene Context is null.");

		Entity entity = scene->GetEntityByUUID(entityID);
		VL_CORE_ASSERT(entity, "Scene Entity is null.");

		MonoType* managedType = mono_reflection_type_get_type(componentType);
		VL_CORE_ASSERT(s_EntityHasComponentFuncs.find(managedType) != s_EntityHasComponentFuncs.end(), "managedType does not exist.");

		return s_EntityHasComponentFuncs.at(managedType)(entity);
	}

	static uint64_t Entity_FindEntityByName(MonoString* name)
	{
		char* nameCStr = mono_string_to_utf8(name);

		Scene* scene = ScriptEngine::GetSceneContext();
		VL_CORE_ASSERT(scene, "ScriptEngine Scene Context is null.");

		Entity entity = scene->FindEntityByName(nameCStr);

		mono_free(nameCStr);
		if (!entity) return 0;	

		return entity.GetUUID();
	}

	#pragma endregion

	#pragma region Components

	static void TransformComponent_GetTranslation(UUID entityID, glm::vec3* outTranslation)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		VL_CORE_ASSERT(scene, "ScriptEngine Scene Context is null.");

		Entity entity = scene->GetEntityByUUID(entityID);
		VL_CORE_ASSERT(entity, "Scene Entity is null.");

		*outTranslation = entity.Transform().Translation;
	}

	static void TransformComponent_SetTranslation(UUID entityID, glm::vec3* translation)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		Entity entity = scene->GetEntityByUUID(entityID);

		entity.Transform().Translation = *translation;
	}

	static void Rigidbody2DComponent_ApplyLinearImpulse(UUID entityID, glm::vec2* impulse, glm::vec2* point, bool wake)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		VL_CORE_ASSERT(scene, "ScriptEngine Scene Context is null.");

		Entity entity = scene->GetEntityByUUID(entityID);
		VL_CORE_ASSERT(entity, "Scene Entity is null.");

		auto& rb2d = entity.GetComponent<Rigidbody2DComponent>();
		b2Body* body = (b2Body*)rb2d.RuntimeBody;
		body->ApplyLinearImpulse(b2Vec2(impulse->x, impulse->y), b2Vec2(point->x, point->y), wake);
	}

	static void Rigidbody2DComponent_ApplyLinearImpulseToCenter(UUID entityID, glm::vec2* impulse, bool wake)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		VL_CORE_ASSERT(scene, "ScriptEngine Scene Context is null.");

		Entity entity = scene->GetEntityByUUID(entityID);
		VL_CORE_ASSERT(entity, "Scene Entity is null.");

		auto& rb2d = entity.GetComponent<Rigidbody2DComponent>();
		b2Body* body = (b2Body*)rb2d.RuntimeBody;
		body->ApplyLinearImpulseToCenter(b2Vec2(impulse->x, impulse->y), wake);
	}

	#pragma endregion

	#pragma region Input

	static bool Input_IsKeyHeld(KeyCode keycode)
	{
		return Input::IsKeyHeld(keycode);
	}

	static bool Input_IsMouseButtonDown(MouseButton mousebutton)
	{
		return Input::IsMouseButtonHeld(mousebutton);
	}

	#pragma endregion
	
	template<typename... Component>
	static void RegisterComponent()
	{
		([]()
			{
				std::string_view typeName = typeid(Component).name();
				size_t pos = typeName.find_last_of(':');
				std::string_view structName = typeName.substr(pos + 1);
				std::string managedTypename = fmt::format("Vinyl.{}", structName);
				MonoType* managedType = mono_reflection_type_from_name(managedTypename.data(), ScriptEngine::GetCoreAssemblyImage());
				if (!managedType)
				{
					VL_CORE_ERROR("Could not find component type {}", managedTypename);
					return;
				}
				s_EntityHasComponentFuncs[managedType] = [](Entity entity) { return entity.HasComponent<Component>(); };
			}(), ...);
	}

	template<typename... Component>
	static void RegisterComponent(ComponentGroup<Component...>)
	{
		RegisterComponent<Component...>();
	}

	void ScriptGlue::RegisterComponents()
	{
		s_EntityHasComponentFuncs.clear();
		RegisterComponent(AllComponents{});
	}

	void ScriptGlue::RegisterFunctions()
	{
		VL_ADD_INTERNAL_CALL(GetScriptInstance);

		VL_ADD_INTERNAL_CALL(Entity_HasComponent);
		VL_ADD_INTERNAL_CALL(Entity_FindEntityByName);

		VL_ADD_INTERNAL_CALL(TransformComponent_GetTranslation);
		VL_ADD_INTERNAL_CALL(TransformComponent_SetTranslation);

		VL_ADD_INTERNAL_CALL(Rigidbody2DComponent_ApplyLinearImpulse);
		VL_ADD_INTERNAL_CALL(Rigidbody2DComponent_ApplyLinearImpulseToCenter);

		VL_ADD_INTERNAL_CALL(Input_IsKeyHeld);
		VL_ADD_INTERNAL_CALL(Input_IsMouseButtonDown);
	}
}