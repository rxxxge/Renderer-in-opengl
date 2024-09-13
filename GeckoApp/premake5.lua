project "GeckoApp"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	targetdir "bin/%{cfg.buildcfg}"
	staticruntime "off"

	files { "src/**.h", "src/**.cpp" }

	includedirs
	{
		"../Gecko/src",
		"../vendor/Glad/include",
		"../vendor/glfw/include",
		"../vendor/glm",
		"../vendor/spdlog/include",
		"../vendor/stb",
	}

	links
	{
		"Gecko"
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
		kind "WindowedApp"
		defines { "GK_DIST" }
		runtime "Release"
		optimize "On"
		symbols "Off"