project "GL"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	targetdir "bin/%{cfg.buildcfg}"
	staticruntime "off"

	files { "src/**.h", "src/**.cpp" }

	includedirs
	{
		"src",
		"../vendor/glfw/include",
	}

	links
	{
		"GLFW"
	}

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

	filter "system:windows"
		systemversion "latest"
		defines { "X_PLATFORM_WINDOWS" }

	filter "configurations:Debug"
		defines { "X_DEBUG", "X_ENABLE_ASSERTS" }
		runtime "Debug"
		symbols "On"
	
	filter "configurations:Release"
		defines { "X_RELEASE" }
		runtime "Release"
		optimize "On"
		symbols "On"

	filter "configurations:Dist"
		defines { "X_DIST" }
		runtime "Release"
		optimize "On"
		symbols "Off"