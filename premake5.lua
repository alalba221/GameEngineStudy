-- premake5.lua
include "Dependencies.lua"

workspace "AlalbaEngine"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   targetdir "build"
 
   startproject "Sandbox"
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


group "Dependencies"
include "AlalbaEngine/vendor/GLFW"
include "AlalbaEngine/vendor/imgui-docking"
group ""


include "AlalbaEngine"
include "Sandbox"
include "RayTracer"