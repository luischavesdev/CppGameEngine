project "Engine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    targetdir "Binaries/%{cfg.buildcfg}"
    staticruntime "off"

    files { "Source/**.h", "Source/**.cpp", "Source/**.c" }

    includedirs
    {
        "Source",
        "../include/box2d",
        "../include/glad",
        "../include/glm",
        "../include/SDL2",
        "../include/stbimage"
    }

    libdirs { "../lib" }
    links { "SDL2", "SDL2_mixer" }

    targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
    objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

    
    filter "system:windows"
        systemversion "latest"
        defines { "WINDOWS" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        links { "box2ddebug" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        links { "box2drelease" }
        runtime "Release"
        optimize "On"
        symbols "Off"