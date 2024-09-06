workspace "GLApp"
	architecture "x64"
	configurations { "Debug", "Release", "Dist" }
	startproject "GLApp"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "GL/GLExternal.lua"
include "GLApp"