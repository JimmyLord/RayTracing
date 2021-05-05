workspace "RayTracingWorkspace"
	configurations	{ "Debug", "Release" }
	platforms		{ "x64" }
	location		"build"
	characterset	"MBCS"
	startproject	"RayTracing"

	filter "configurations:Debug"
		symbols		"on"

project "RayTracing"
	kind		"WindowedApp"
	location	"build/RayTracing"
	debugdir	"RayTracing"

	files {
		"RayTracing/Source/**.cpp",
		"RayTracing/Source/**.h",
		"Libraries/imgui/*.cpp",
		"Libraries/imgui/*.h",
		"premake5.lua",
		".gitignore",
		"GenerateProjectFiles.bat",
	}

	includedirs {
		"RayTracing/Source",
	}

	links {
		"opengl32",
	}

	pchheader "PCH.h"
	pchsource "RayTracing/Source/PCH.cpp"

	filter "files:Libraries/imgui/*.cpp"
		flags { "NoPCH" }
