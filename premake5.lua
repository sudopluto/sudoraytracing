-- premake5.lua
workspace "sudoraytracer"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "sudoraytracer"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
include "Walnut/WalnutExternal.lua"

include "sudoraytracer"
