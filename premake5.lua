workspace "Vinyl"
	architecture "x64"

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

include "Vinyl/Vendor/GLFW"

project "Vinyl"
	location "Vinyl"
	kind "SharedLib"
	language "C++"

	targetdir ("Bin/" .. outputdir .. "/%{prj.name}")
	objdir ("Bin-Intermediates/" .. outputdir .. "/%{prj.name}")

	pchheader "vlpch.h"
	pchsource "Vinyl/Source/vlpch.cpp"

	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/Source/",
		"%{prj.name}/Vendor/SpdLog/include",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib",
		"dwmapi.lib"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"VL_PLATFORM_WINDOWS",
			"VL_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../Bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "VL_DEBUG"
		optimize "On"

	filter "configurations:Release"
		defines "VL_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "VL_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		"Vinyl/Source"
	}

	links
	{
		"Vinyl"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"VL_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "VL_DEBUG"
		optimize "On"

	filter "configurations:Release"
		defines "VL_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "VL_DIST"
		optimize "On"