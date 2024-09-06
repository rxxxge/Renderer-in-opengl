project "GLApp"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	targetdir "bin/%{cfg.buildcfg}"
	staticruntime "off"

	files { "src/**.h", "src/**.cpp" }

	includedirs
	{
		"../vendor/glfw/include",
		"../GL/src",
	}

	links
	{
		"GL"
	}

	targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

	filter "system:windows"
		systemversion "latest"
		defines { "X_PLATFORM_WINDOWS" }

	filter "configurations:Debug"
		defines { "X_DEBUG" }
		runtime "Debug"
		symbols "On"
	
	filter "configurations:Release"
		defines { "X_RELEASE" }
		runtime "Release"
		optimize "On"
		symbols "On"

	filter "configurations:Dist"
		kind "WindowedApp"
		defines { "X_DIST" }
		runtime "Release"
		optimize "On"
		symbols "Off"