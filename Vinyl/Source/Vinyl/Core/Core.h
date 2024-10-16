#pragma once

#include <memory>

#ifdef VL_PLATFORM_WINDOWS
#if VL_DYNAMIC_LINK
	#ifdef VL_BUILD_DLL
		#define VINYL_API __declspec(dllexport)
	#else
		#define VINYL_API __declspec(dllimport)
	#endif // VL_BUILD_DLL
#else
	#define VINYL_API
#endif
#else
	#error Vinyl only supports windows.
#endif // VL_PLATFORM_WINDOWS

#ifdef VL_DEBUG
	#define VL_ENABLE_ASSERTS
#endif

#ifdef VL_ENABLE_ASSERTS
#define VL_ASSERT(x, ...) { if(!(x)) { VL_ERROR("Assertion Failed: {}", fmt::format(__VA_ARGS__)); __debugbreak(); } }
#define VL_CORE_ASSERT(x, ...) { if(!(x)) { VL_CORE_ERROR("Assertion Failed: {}", fmt::format(__VA_ARGS__)); __debugbreak(); } }
#else
#define VL_ASSERT(x, ...)
#define VL_CORE_ASSERT(x, ...)
#endif

//Keeping old asserts just in case i get bugs with the new Asserts
/*
#ifdef VL_ENABLE_ASSERTS
	#define VL_ASSERT(x, ...) { if(!(x)) { VL_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define VL_CORE_ASSERT(x, ...) {if(!(x)) { VL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define VL_ASSERT(x, ...)
	#define VL_CORE_ASSERT(x, ...)
#endif
*/

#define BIT(x) (1 << x)

#define VL_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Vinyl
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}