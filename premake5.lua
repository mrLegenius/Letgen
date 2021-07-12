workspace "Letgen"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Distribution"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Letgen/vendor/GLFW/include"

include "Letgen/vendor/GLFW"

project "Letgen"
    location "Letgen"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "LE_PLATFORM_WINDOWS",
            "LE_BUILD_DLL"
        }

        links
        {
            "GLFW",
            "opengl32.lib"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "LE_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "LE_RELEASE"
        optimize "On"

    filter "configurations:Distribution"
        defines "LE_DIST"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

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
        "Letgen/src"
    }

    links
    {
        "Letgen"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "LE_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "LE_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "LE_RELEASE"
        optimize "On"

    filter "configurations:Distribution"
        defines "LE_DIST"
        optimize "On"