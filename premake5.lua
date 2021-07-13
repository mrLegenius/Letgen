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

group "Dependencies"
    include "Letgen/vendor/GLFW"
    include "Letgen/vendor/GLAD"
    include "Letgen/vendor/ImGui"
group ""

project "Letgen"
    location "Letgen"
    kind "SharedLib"
    language "C++"
    staticruntime "off"

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
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLAD}",
        "%{IncludeDir.ImGui}"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            "LE_PLATFORM_WINDOWS",
            "LE_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        links
        {
            "GLFW",
            "GLAD",
            "ImGui",
            "opengl32.lib"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox\"")
        }

    filter "configurations:Debug"
        defines "LE_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "LE_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Distribution"
        defines "LE_DIST"
        runtime "Release"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    staticruntime "off"

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
        systemversion "latest"

        defines
        {
            "LE_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "LE_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "LE_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Distribution"
        defines "LE_DIST"
        runtime "Release"
        optimize "On"