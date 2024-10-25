#pragma once

#include "Vinyl/Core/Base.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

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

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
{
	return os << glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
{
	return os << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternion)
{
	return os << glm::to_string(quaternion);
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