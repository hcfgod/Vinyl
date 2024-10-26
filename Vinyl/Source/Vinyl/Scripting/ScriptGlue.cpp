#include "vlpch.h"

#include "ScriptGlue.h"

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

	void ScriptGlue::RegisterFunctions()
	{
		VL_ADD_INTERNAL_CALL(NativeLog);
		VL_ADD_INTERNAL_CALL(NativeLog_Vector);
	}
}