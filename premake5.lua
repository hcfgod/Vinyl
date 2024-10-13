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
IncludeDir["Glad"] = "Vinyl/Vendor/Glad/include"

include "Vinyl/Vendor/GLFW"
include "Vinyl/Vendor/Glad"

project "Vinyl"
	location "Vinyl"
	kind "SharedLib"
	language "C++"
	cppdialect "C++20"

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
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}"
	}

	links
	{
		"GLFW",
		"Glad",
		"opengl32.lib",
		"dwmapi.lib"
	}

	filter "system:windows"
		systemversion "latest"
		staticruntime "Off"
		defines
		{
			"VL_PLATFORM_WINDOWS",
			"VL_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../Bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "VL_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "VL_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "VL_DIST"
		buildoptions "/MD"
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
		staticruntime "Off"
		systemversion "latest"

		defines
		{
			"VL_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "VL_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "VL_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "VL_DIST"
		optimize "On"