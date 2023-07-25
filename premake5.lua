include "./vendor/premake/premake_customization/solution_items.lua"
include "Dependencies.lua"

workspace "Pacman"
	architecture "x86_64"
	startproject "Pacman"

	configurations
	{
		"Debug",
		"Release"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "vendor/premake"
	include "Pacman/vendor/GLFW"
	include "Pacman/vendor/Glad"
group ""

group "Game"
	include "Pacman"
group ""