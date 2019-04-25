newoption {
  trigger = "SFML_INSTALL_DIR",
  value = "path",
  description = "Path to SFML install directory"
}

workspace "checkers"
  configurations {"Debug", "Release"}

project "checkers"
  kind "ConsoleApp"
  language "C++"
  targetdir "bin/%{cfg.buildcfg}"

  files {"**.hpp", "**.cpp"}

  includedirs "include"
  includedirs (_OPTIONS["SFML_INSTALL_DIR"] .. "/" .. "include")
  libdirs (_OPTIONS["SFML_INSTALL_DIR"] .. "/" .. "lib")

  filter "configurations:Debug"
    defines "DEBUG"
    symbols "On"
    links {"sfml-audio-d", "sfml-graphics-d", "sfml-system-d", "sfml-window-d"}

  filter "configurations:Release"
    defines "NDEBUG"
    optimize "On"
    links {"sfml-audio", "sfml-graphics", "sfml-system", "sfml-window"}
