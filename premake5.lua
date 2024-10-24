workspace "Vinyl"
	architecture "x64"
	startproject "Vinyl-Editor"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Vinyl/Vendor/GLFW/include"
IncludeDir["Glad"] = "Vinyl/Vendor/Glad/include"
IncludeDir["imgui"] = "Vinyl/Vendor/imgui"
IncludeDir["glm"] = "Vinyl/Vendor/glm"
IncludeDir["stb_image"] = "Vinyl/Vendor/stb_image"
IncludeDir["entt"] = "Vinyl/Vendor/entt/include"
IncludeDir["yaml_cpp"] = "Vinyl/Vendor/yaml-cpp/include"
IncludeDir["ImGuizmo"] = "Vinyl/Vendor/ImGuizmo"
IncludeDir["shaderc"] = "Vinyl/Vendor/shaderc/include"
IncludeDir["SPIRV_Cross"] = "Vinyl/Vendor/SPIRV-Cross"
IncludeDir["VulkanSDK"] = "Vinyl/Vendor/VulkanSDK/Include"

-- Libraries to link
--Library = {}
--Library["Vulkan"] = "Vinyl/Vendor/VulkanSDK/Lib/vulkan-1.lib"


group "Dependencies"
	include "Vinyl/Vendor/GLFW"
	include "Vinyl/Vendor/Glad"
	include "Vinyl/Vendor/imgui"
	include "Vinyl/Vendor/yaml-cpp"
group ""

project "Vinyl"
	location "Vinyl"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	targetdir ("Bin/" .. outputdir .. "/%{prj.name}")
	objdir ("Bin-Intermediates/" .. outputdir .. "/%{prj.name}")

	pchheader "vlpch.h"
	pchsource "Vinyl/Source/vlpch.cpp"

	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp",

		"%{prj.name}/Vendor/stb_image/**.h",
		"%{prj.name}/Vendor/stb_image/**.cpp",

		"%{prj.name}/Vendor/glm/glm/**.hpp",
		"%{prj.name}/Vendor/glm/glm/**.inl",

		"%{prj.name}/Vendor/ImGuizmo/ImGuizmo.h",
		"%{prj.name}/Vendor/ImGuizmo/ImGuizmo.cpp",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"YAML_CPP_STATIC_DEFINE",
		"IMGUI_DEFINE_MATH_OPERATORS",
		"GLM_FORCE_QUAT_DATA_WXYZ"
	}

	includedirs
	{
		"%{prj.name}/Source/",
		"%{prj.name}/Vendor/SpdLog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.ImGuizmo}",
		"%{IncludeDir.shaderc}",
		"%{IncludeDir.SPIRV_Cross}",
		"%{IncludeDir.VulkanSDK}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"yaml-cpp",
		"dwmapi.lib",
		"Vinyl/Vendor/VulkanSDK/Lib/vulkan-1.lib",
		"Vinyl/Vendor/VulkanSDK/Lib/shaderc_sharedd.lib",
		"Vinyl/Vendor/VulkanSDK/Lib/spirv-cross-cored.lib",
		"Vinyl/Vendor/VulkanSDK/Lib/spirv-cross-glsld.lib",
		"Vinyl/Vendor/VulkanSDK/Lib/shaderc_shared.lib",
		"Vinyl/Vendor/VulkanSDK/Lib/spirv-cross-core.lib",
		"Vinyl/Vendor/VulkanSDK/Lib/spirv-cross-glsl.lib"
	}

	filter "files:Vinyl/Vendor/ImGuizmo/**.cpp"
		flags { "NoPCH" }

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"VL_PLATFORM_WINDOWS",
			"VL_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
		}

	filter "configurations:Debug"
		defines "VL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "VL_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "VL_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	targetdir ("Bin/" .. outputdir .. "/%{prj.name}")
	objdir ("Bin-Intermediates/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp",
	}

	includedirs
	{
		"Vinyl/Vendor/SpdLog/include",
		"Vinyl/Source",
		"Vinyl/Vendor/",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}"
	}

	links
	{
		"Vinyl"
	}

	filter "system:windows"
		systemversion "latest"

	defines
	{
		"VL_PLATFORM_WINDOWS",
	}

	filter "configurations:Debug"
		defines "VL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "VL_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "VL_DIST"
		runtime "Release"
		optimize "on"

project "Vinyl-Editor"
	location "Vinyl-Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	targetdir ("Bin/" .. outputdir .. "/%{prj.name}")
	objdir ("Bin-Intermediates/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp",
	}

	includedirs
	{
		"Vinyl/Vendor/SpdLog/include",
		"Vinyl/Source",
		"Vinyl/Vendor/",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.ImGuizmo}",
	}

	links
	{
		"Vinyl"
	}

	filter "system:windows"
		systemversion "latest"

	defines
	{
		"VL_PLATFORM_WINDOWS"
	}

	filter "configurations:Debug"
		defines "VL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "VL_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "VL_DIST"
		runtime "Release"
		optimize "on"