#pragma once
#include "Vinyl/Core/Base.h"
#include "Vinyl/Core/Log.h"

#ifdef VL_ENABLE_ASSERTS
#define VL_ASSERT(x, ...) { if(!(x)) { VL_ERROR("Assertion Failed: {}", fmt::format(__VA_ARGS__)); __debugbreak(); } }
#define VL_CORE_ASSERT(x, ...) { if(!(x)) { VL_CORE_ERROR("Assertion Failed: {}", fmt::format(__VA_ARGS__)); __debugbreak(); } }
#else
#define VL_ASSERT(x, ...)
#define VL_CORE_ASSERT(x, ...)
#endif

/*
#ifdef VL_ENABLE_ASSERTS
namespace Vinyl::Assert
{
	// Returns the simple file name rather than full path as suggested by LovelySanta
	constexpr const char* CurrentFileName(const char* path) {
		const char* file = path;
		while (*path)
		{
			if (*path == '/' || *path == '\\')
				file = ++path;
			else
				path++;
		}
		return file;
	}
}
// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define VL_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { VL##type##ERROR(msg, __VA_ARGS__); VL_DEBUGBREAK(); } }
#define VL_INTERNAL_ASSERT_WITH_MSG(type, check, ...) VL_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define VL_INTERNAL_ASSERT_NO_MSG(type, check) VL_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", VL_STRINGIFY_MACRO(check), ::Vinyl::Assert::CurrentFileName(__FILE__), __LINE__)
#define VL_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define VL_INTERNAL_ASSERT_GET_MACRO(...) VL_EXPAND_MACRO( VL_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, VL_INTERNAL_ASSERT_WITH_MSG, VL_INTERNAL_ASSERT_NO_MSG) )
// Currently accepts at least the condition and one additional parameter (the message) being optional
#define VL_ASSERT(...) VL_EXPAND_MACRO( VL_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#define VL_CORE_ASSERT(...) VL_EXPAND_MACRO( VL_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
#define VL_ASSERT(...)
#define VL_CORE_ASSERT(...)
#endif
*/