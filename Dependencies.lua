-- Dependecies.lua

VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"
IncludeDir["VMA"] = "%{wks.location}/AlalbaEngine/vendor/VMA/include"
IncludeDir["glm"] = "%{wks.location}/AlalbaEngine/vendor/glm"
IncludeDir["GLFW"] = "%{wks.location}/AlalbaEngine/vendor/GLFW/include"
IncludeDir["spdlog"] = "%{wks.location}/AlalbaEngine/vendor/spdlog/include"
IncludeDir["Assimp"] = "%{wks.location}/AlalbaEngine/vendor/assimp/include"
IncludeDir["tinyobj"] = "%{wks.location}/AlalbaEngine/vendor/tiny_obj_loader"
IncludeDir["tinygltf"] = "%{wks.location}/AlalbaEngine/vendor/tinygltf"
IncludeDir["stb"] = "%{wks.location}/AlalbaEngine/vendor/stb/include"
IncludeDir["ImGui"] = "%{wks.location}/AlalbaEngine/vendor/imgui-docking"
IncludeDir["entt"] = "%{wks.location}/AlalbaEngine/vendor/entt/include"



LibraryDir = {}
LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"

Library = {}
Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
Library["Assimp_Debug"] = "%{wks.location}/AlalbaEngine/vendor/assimp/bin/Debug/assimp-vc142-mtd.lib"
Library["Assimp_Release"] = "%{wks.location}/AlalbaEngine/vendor/assimp/bin/Release/assimp-vc142-mt.lib"


-- Shared Lib
Binaries = {}
Binaries["Assimp_Debug"] = "%{wks.location}/AlalbaEngine/vendor/assimp/bin/Debug/assimp-vc142-mtd.dll"
Binaries["Assimp_Release"] = "%{wks.location}/AlalbaEngine/vendor/assimp/bin/Release/assimp-vc142-mt.dll"
