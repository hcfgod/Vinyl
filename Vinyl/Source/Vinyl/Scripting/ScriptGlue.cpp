#include "vlpch.h"

#include "Vinyl/Scripting/ScriptGlue.h"
#include "Vinyl/Scripting/ScriptEngine.h"

#include "Vinyl/Scene/Scene.h"
#include "Vinyl/Scene/Entity.h"

#include "Vinyl/Core/UUID.h"

#include "Vinyl/Core/Input/Input.h"
#include "Vinyl/Core/Input/KeyCodes.h"
#include "Vinyl/Core/Input/MouseCodes.h"

#include <mono/metadata/object.h>

#define VL_ADD_INTERNAL_CALL(Name) mono_add_internal_call("Vinyl.InternalCalls::"#Name, Name)

namespace Vinyl
{
	static void NativeLog(MonoString* monoString, int paramater)
	{
		char* cString = mono_string_to_utf8(monoString);
		std::string string(cString);

		mono_free(cString);

		std::cout << string << ":" << paramater << std::endl;
	}

	static void NativeLog_Vector(glm::vec3* paramater, glm::vec3* outResult)
	{
		VL_CORE_WARN("Value: {0}", *paramater);

		auto testVec = glm::vec3(1.0f, 0.5f, 2.5f);
		auto cross = glm::cross(*paramater, testVec);

		*outResult = cross;
	}

	static void Entity_GetTranslation(UUID entityID, glm::vec3* outTranslation)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		Entity entity = scene->GetEntityByUUID(entityID);

		*outTranslation = entity.Transform().Translation;
	}

	static void Entity_SetTranslation(UUID entityID, glm::vec3* translation)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		Entity entity = scene->GetEntityByUUID(entityID);

		entity.Transform().Translation = *translation;
	}

	static bool Input_IsKeyDown(KeyCode keycode)
	{
		return Input::IsKeyDown(keycode);
	}

	static bool Input_IsMouseDown(MouseCode mousecode)
	{
		return Input::IsMouseDown(mousecode);
	}

	void ScriptGlue::RegisterFunctions()
	{
		VL_ADD_INTERNAL_CALL(NativeLog);
		VL_ADD_INTERNAL_CALL(NativeLog_Vector);

		VL_ADD_INTERNAL_CALL(Entity_GetTranslation);
		VL_ADD_INTERNAL_CALL(Entity_SetTranslation);

		VL_ADD_INTERNAL_CALL(Input_IsKeyDown);
		VL_ADD_INTERNAL_CALL(Input_IsMouseDown);
	}
}