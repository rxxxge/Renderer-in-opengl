workspace "Gecko"
	architecture "x64"
	configurations { "Debug", "Release", "Dist" }
	startproject "GeckoApp"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Gecko/GeckoExternal.lua"
include "GeckoApp"