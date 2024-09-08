project "Gecko"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	targetdir "bin/%{cfg.buildcfg}"
	staticruntime "off"

	pchheader "gkpch.h"
   	pchsource "src/gkpch.cpp"

	files { "src/**.h", "src/**.cpp" }

	includedirs
	{
		"src",
		"../vendor/glfw/include",
		"../vendor/Glad/include"
	}

	links
	{
		"GLFW",
		"GLAD",
		"opengl32.lib"
	}

	targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

	filter "system:windows"
		systemversion "latest"
		defines { "GK_PLATFORM_WINDOWS" }

	filter "configurations:Debug"
		defines { "GK_DEBUG" }
		runtime "Debug"
		symbols "On"
	
	filter "configurations:Release"
		defines { "GK_RELEASE" }
		runtime "Release"
		optimize "On"
		symbols "On"

	filter "configurations:Dist"
		defines { "GK_DIST" }
		runtime "Release"
		optimize "On"
		symbols "Off"