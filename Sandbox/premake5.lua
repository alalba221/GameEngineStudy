project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
	staticruntime "on"
    --staticruntime "off"
	files { "source/**.h", "source/**.cpp" }

   includedirs
   {
		"%{wks.location}/engine/source",
		"%{wks.location}/engine/3rdparty",
      
      -- except for GLFW, all is header only
      -- Why include GLFW: in the Windwo.h includes glfw. This is needed to be fixed
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.VulkanSDK}", 
		"%{IncludeDir.VMA}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.tinyobj}",
		"%{IncludeDir.tinygltf}",
		"%{IncludeDir.GLFW}",
		--"%{IncludeDir.stb}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.entt}",

   }
   --prebuildcommands [[for %%i in (shaders\*.vert shaders\*.frag) do (C:\VulkanSDK\1.3.239.0\Bin\glslc.exe %%i -o "%%~dpi\%%~ni.spv")]]
   -- prebuildcommands [[for %%i in (shaders\*.vert shaders\*.frag) do (C:\VulkanSDK\1.3.239.0\Bin\glslc.exe %%i -o "%%~dpi\%%~nxi.spv")]]
    links
    {
        "Engine"
    }

    defines
	{

		"GLM_FORCE_DEPTH_ZERO_TO_ONE",
		"GLM_FORCE_RADIANS",
		--"VMA_IMPLEMENTATION",
		""
	}
   targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
   objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

   filter "system:windows"
      systemversion "latest"
      defines { "ALALBA_PLATFORM_WINDOWS" }

   filter "configurations:Debug"
      defines { "ALALBA_DEBUG" }
      runtime "Debug"
      symbols "On"
      
      links
		{
			--"%{Library.Assimp_Debug}"
		}
        postbuildcommands 
		{
			--'{COPY} "%{Binaries.Assimp_Debug}" "%{cfg.targetdir}"'
		}

   filter "configurations:Release"
      defines { "ALALBA_RELEASE" }
      runtime "Release"
      optimize "On"
      symbols "On"
      links
		{
			--"%{Library.Assimp_Release}"
		}
       postbuildcommands 
		{
			--'{COPY} "%{Binaries.Assimp_Release}" "%{cfg.targetdir}"'
		}


   filter "configurations:Dist"
      kind "WindowedApp"
      defines { "ALALBA_DIST" }
      runtime "Release"
      optimize "On"
      symbols "Off"
      links
		{
			--"%{Library.Assimp_Release}"
		}
       postbuildcommands 
		{
			--'{COPY} "%{Binaries.Assimp_Release}" "%{cfg.targetdir}"'
		}