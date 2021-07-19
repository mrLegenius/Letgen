workspace "Letgen"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Distribution"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}

IncludeDir["GLFW"] = "Letgen/vendor/GLFW/include"
IncludeDir["GLAD"] = "Letgen/vendor/GLAD/include"
IncludeDir["ImGui"] = "Letgen/vendor/ImGui"
IncludeDir["GLM"] = "Letgen/vendor/GLM"
IncludeDir["stb_image"] = "Letgen/vendor/stb_image"

group "Dependencies"
    include "Letgen/vendor/GLFW"
    include "Letgen/vendor/GLAD"
    include "Letgen/vendor/ImGui"
group ""

project "Letgen"
    location "Letgen"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "pch.h"
    pchsource "Letgen/src/pch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/stb_image/**.h",
        "%{prj.name}/vendor/stb_image/**.cpp",
        "%{prj.name}/vendor/GLM/glm/**.hpp",
        "%{prj.name}/vendor/GLM/glm/**.inl"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLAD}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.GLM}",
        "%{IncludeDir.stb_image}"
    }

    links
    {
        "GLFW",
        "GLAD",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"

        systemversion "latest"

        defines
        {
            "LE_PLATFORM_WINDOWS",
            "LE_BUILD_DLL",
            "GLFW_INCLUDE_NONE",
        }

    filter "configurations:Debug"
        defines "LE_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "LE_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Distribution"
        defines "LE_DIST"
        runtime "Release"
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Letgen/vendor/spdlog/include",
        "Letgen/src",
        "Letgen/vendor",
        "%{IncludeDir.GLM}"
    }

    links
    {
        "Letgen"
    }

    filter "system:windows"
        systemversion "latest"
   
    defines
    {
        "LE_PLATFORM_WINDOWS"
    }

    filter "configurations:Debug"
        defines "LE_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "LE_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Distribution"
        defines "LE_DIST"
        runtime "Release"
        optimize "on"

project "LetEditor"
    location "LetEditor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Letgen/vendor/spdlog/include",
        "Letgen/src",
        "Letgen/vendor",
        "%{IncludeDir.GLM}"
    }

    links
    {
        "Letgen"
    }

    filter "system:windows"
        systemversion "latest"

    defines
    {
        "LE_PLATFORM_WINDOWS"
    }

    filter "configurations:Debug"
        defines "LE_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "LE_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Distribution"
        defines "LE_DIST"
        runtime "Release"
        optimize "on"