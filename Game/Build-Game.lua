project "Game"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir "Binaries/%{cfg.buildcfg}"
    staticruntime "off"

    files { "Source/**.h", "Source/**.cpp" }

    includedirs { "Source", "../Engine/Source" }

    links { "Engine" }

    targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
    objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

    
    filter "system:windows"
        systemversion "latest"
        defines { "WINDOWS" }
        postbuildcommands
        {
            "{COPYFILE} ../Binaries/" .. OutputDir .. "/Engine/*.lib ../Binaries/" .. OutputDir .. "/Game",
            "{COPYFILE} ../lib/*.dll ../Binaries/" .. OutputDir .. "/Game",
            "{COPYDIR} ../Game/data ../Binaries/" .. OutputDir .. "/Game/data"
        }


    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        runtime "Release"
        optimize "On"
        symbols "Off"