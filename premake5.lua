newoption {
  trigger = "SFML_INSTALL_DIR",
  value = "path",
  description = "Path to SFML install directory"
}

SFML_INSTALL_DIR = _OPTIONS["SFML_INSTALL_DIR"]
WINDOWS = os.host() == "windows"
LINUX = os.host() == "linux"

if _ACTION and string.startswith(_ACTION, "vs20") and not SFML_INSTALL_DIR then
  error("Please specify path to SFML install directory via SFML_INSTALL_DIR")
end

workspace "checkers"
  configurations {"Debug", "Release"}

project "checkers"
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++17"
  targetdir "bin/%{cfg.buildcfg}"

  files {"**.hpp", "**.cpp"}

  includedirs "include"

  if WINDOWS then
    includedirs (path.join(SFML_INSTALL_DIR, "include"))
    libdirs (path.join(SFML_INSTALL_DIR, "lib"))
  elseif LINUX then
    links "stdc++fs"
  end

  filter "configurations:Release"
    defines "NDEBUG"
    optimize "On"
    links {"sfml-audio", "sfml-graphics", "sfml-system", "sfml-window"}

  filter "configurations:Debug"
    defines "DEBUG"
    symbols "On"
    
    if WINDOWS then
      links {"sfml-audio-d", "sfml-graphics-d", "sfml-system-d", "sfml-window-d"}
    elseif LINUX then
      links {"sfml-audio", "sfml-graphics", "sfml-system", "sfml-window"}
    end

