#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include "Vinyl/Core/Base.h"

namespace Vinyl
{
	class VINYL_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define VL_CORE_TRACE(...)    ::Vinyl::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define VL_CORE_INFO(...)     ::Vinyl::Log::GetCoreLogger()->info(__VA_ARGS__)
#define VL_CORE_WARN(...)     ::Vinyl::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define VL_CORE_ERROR(...)    ::Vinyl::Log::GetCoreLogger()->error(__VA_ARGS__)
#define VL_CORE_CRITICAL(...) ::Vinyl::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define VL_TRACE(...)         ::Vinyl::Log::GetClientLogger()->trace(__VA_ARGS__)
#define VL_INFO(...)          ::Vinyl::Log::GetClientLogger()->info(__VA_ARGS__)
#define VL_WARN(...)          ::Vinyl::Log::GetClientLogger()->warn(__VA_ARGS__)
#define VL_ERROR(...)         ::Vinyl::Log::GetClientLogger()->error(__VA_ARGS__)
#define VL_CRITICAL(...)      ::Vinyl::Log::GetClientLogger()->critical(__VA_ARGS__)