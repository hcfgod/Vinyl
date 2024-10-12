#pragma once

#ifdef VL_PLATFORM_WINDOWS
	#ifdef VL_BUILD_DLL
		#define VINYL_API __declspec(dllexport)
	#else
		#define VINYL_API __declspec(dllimport)
	#endif // VL_BUILD_DLL
#else
	#error Vinyl only supports windows.
#endif // VL_PLATFORM_WINDOWS

namespace Vinyl
{

}