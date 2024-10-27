#pragma once

#include "Vinyl/Core/Base.h"
#include "Vinyl/Core/UUID.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

#include <filesystem>

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

// Specialization for glm::vec types to work with fmt and spdlog
template <glm::length_t L, typename T, glm::qualifier Q>
struct fmt::formatter<glm::vec<L, T, Q>> 
{
	// Parse format specification (can be extended)
	constexpr auto parse(fmt::format_parse_context& ctx) -> decltype(ctx.begin())
	{
		return ctx.begin();
	}

	// Format the glm::vec object using glm::to_string
	template <typename FormatContext>
	auto format(const glm::vec<L, T, Q>& vec, FormatContext& ctx) const -> decltype(ctx.out()) 
	{
		// Use fmt::format instead of format_to for clarity
		return fmt::format_to(ctx.out(), "{}", glm::to_string(vec));
	}
};

// Specialization for glm::mat types to work with fmt and spdlog
template <glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
struct fmt::formatter<glm::mat<C, R, T, Q>>
{
	// Parse format specification (can be extended)
	constexpr auto parse(fmt::format_parse_context& ctx) -> decltype(ctx.begin())
	{
		return ctx.begin();
	}

	// Format the glm::mat object using glm::to_string
	template <typename FormatContext>
	auto format(const glm::mat<C, R, T, Q>& matrix, FormatContext& ctx) const -> decltype(ctx.out())
	{
		// Use fmt::format_to to format the matrix
		return fmt::format_to(ctx.out(), "{}", glm::to_string(matrix));
	}
};

// Specialization for glm::qua (quaternion) types to work with fmt and spdlog
template <typename T, glm::qualifier Q>
struct fmt::formatter<glm::qua<T, Q>>
{
	// Parse format specification (can be extended)
	constexpr auto parse(fmt::format_parse_context& ctx) -> decltype(ctx.begin())
	{
		return ctx.begin();
	}

	// Format the glm::qua object using glm::to_string
	template <typename FormatContext>
	auto format(const glm::qua<T, Q>& quaternion, FormatContext& ctx) const -> decltype(ctx.out())
	{
		// Use fmt::format_to to format the quaternion
		return fmt::format_to(ctx.out(), "{}", glm::to_string(quaternion));
	}
};

template <>
struct fmt::formatter<std::filesystem::path> : fmt::formatter<std::string>
{
	// Parses the format specifier (if any)
	template <typename ParseContext>
	constexpr auto parse(ParseContext& ctx) -> decltype(ctx.begin())
	{
		return fmt::formatter<std::string>::parse(ctx);
	}

	// Formats the std::filesystem::path object using fmt::format
	template <typename FormatContext>
	auto format(const std::filesystem::path& path, FormatContext& ctx) const -> decltype(ctx.out())
	{
		return fmt::formatter<std::string>::format(path.string(), ctx);
	}
};

template <>
struct fmt::formatter<Vinyl::UUID>
{
	// Parse format specification (if any)
	constexpr auto parse(fmt::format_parse_context& ctx) -> decltype(ctx.begin()) {
		return ctx.begin();
	}

	// Format the UUID object as a string
	template <typename FormatContext>
	auto format(const Vinyl::UUID& uuid, FormatContext& ctx) const -> decltype(ctx.out()) {
		// Explicitly convert the UUID to a string using fmt::format to avoid ambiguity
		return fmt::format_to(ctx.out(), "{}", static_cast<std::string>(std::to_string(static_cast<uint64_t>(uuid))));
	}
};

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