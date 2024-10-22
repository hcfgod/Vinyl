#pragma once

#include <memory>
#include "Vinyl/Core/PlatformDetection.h"

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

#define VL_EXPAND_MACRO(x) x
#define VL_STRINGIFY_MACRO(x) #x

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

#include "Vinyl/Core/Log.h"
#include "Vinyl/Core/Assert.h"