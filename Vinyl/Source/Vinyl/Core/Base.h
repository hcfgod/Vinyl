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

// TODO: make this macro optionally take in no arguments except condition
#ifdef VL_ENABLE_ASSERTS
#define VL_ASSERT(x, ...) { if(!(x)) { VL_ERROR("Assertion Failed: {}", fmt::format(__VA_ARGS__)); __debugbreak(); } }
#define VL_CORE_ASSERT(x, ...) { if(!(x)) { VL_CORE_ERROR("Assertion Failed: {}", fmt::format(__VA_ARGS__)); __debugbreak(); } }
#else
#define VL_ASSERT(x, ...)
#define VL_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define VL_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Vinyl
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}