workspace "Vinyl"
	architecture "x64"
	startproject "Sandbox"

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

group "Dependencies"
	include "Vinyl/Vendor/GLFW"
	include "Vinyl/Vendor/Glad"
	include "Vinyl/Vendor/imgui"

group ""

project "Vinyl"
	location "Vinyl"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("Bin/" .. outputdir .. "/%{prj.name}")
	objdir ("Bin-Intermediates/" .. outputdir .. "/%{prj.name}")

	pchheader "vlpch.h"
	pchsource "Vinyl/Source/vlpch.cpp"

	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp",
		"%{prj.name}/Vendor/glm/glm/**.hpp",
		"%{prj.name}/Vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/Source/",
		"%{prj.name}/Vendor/SpdLog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib",
		"dwmapi.lib"
	}

	filter "system:windows"
		systemversion "latest"
		cppdialect "C++20"

		defines
		{
			"VL_PLATFORM_WINDOWS",
			"VL_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	postbuildcommands
	{
		("{COPY} %{cfg.buildtarget.relpath} \"../Bin/" .. outputdir .. "/Sandbox/\"")
	}

	filter "configurations:Debug"
		defines "VL_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "VL_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "VL_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
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
		"%{IncludeDir.glm}"
	}

	links
	{
		"Vinyl"
	}

	filter "system:windows"
		cppdialect "C++20"
		systemversion "latest"

	defines
	{
		"VL_PLATFORM_WINDOWS",
	}

	filter "configurations:Debug"
		defines "VL_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "VL_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "VL_DIST"
		runtime "Release"
		optimize "On"