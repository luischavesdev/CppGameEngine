workspace "CppGameEngine"
   architecture "x64"
   configurations { "Debug", "Release" }
   startproject "Game"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

-- Variable is used by each project lua file
OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group "Engine"
   include "Engine/Build-Engine.lua"
group ""

include "Game/Build-Game.lua"