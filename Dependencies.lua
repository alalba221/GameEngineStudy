-- Dependecies.lua

VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"
IncludeDir["VMA"] = "%{wks.location}/engine/3rdparty/VMA/include"
IncludeDir["glm"] = "%{wks.location}/engine/3rdparty/glm"
IncludeDir["GLFW"] = "%{wks.location}/engine/3rdparty/GLFW/include"
IncludeDir["spdlog"] = "%{wks.location}/engine/3rdparty/spdlog/include"
IncludeDir["Assimp"] = "%{wks.location}/engine/3rdparty/assimp/include"
IncludeDir["tinyobj"] = "%{wks.location}/engine/3rdparty/tiny_obj_loader"
IncludeDir["tinygltf"] = "%{wks.location}/engine/3rdparty/tinygltf"
IncludeDir["stb"] = "%{wks.location}/engine/3rdparty/stb/include"
IncludeDir["ImGui"] = "%{wks.location}/engine/3rdparty/imgui-docking"
IncludeDir["entt"] = "%{wks.location}/engine/3rdparty/entt/include"



LibraryDir = {}
LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"

Library = {}
Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
Library["Assimp_Debug"] = "%{wks.location}/engine/3rdparty/assimp/bin/Debug/assimp-vc142-mtd.lib"
Library["Assimp_Release"] = "%{wks.location}/engine/3rdparty/assimp/bin/Release/assimp-vc142-mt.lib"


-- Shared Lib
Binaries = {}
Binaries["Assimp_Debug"] = "%{wks.location}/engine/3rdparty/assimp/bin/Debug/assimp-vc142-mtd.dll"
Binaries["Assimp_Release"] = "%{wks.location}/engine/3rdparty/assimp/bin/Release/assimp-vc142-mt.dll"
