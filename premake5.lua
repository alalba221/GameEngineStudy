-- premake5.lua
include "Dependencies.lua"

workspace "Alalba"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   targetdir "build"
 
   startproject "sandbox"
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


group "Dependencies"
include "engine/3rdparty/GLFW"
include "engine/3rdparty/imgui-docking"
group ""


include "engine"
include "sandbox"
-- include "RayTracer"