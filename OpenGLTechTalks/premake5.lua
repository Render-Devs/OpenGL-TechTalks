workspace "OpenGLTechTalks"
  architecture "x64"

  configurations
  {
    "Dubug",
    "Release"
  }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "ThirdParty/GLFW/include"
IncludeDir["Glad"] = "ThirdParty/Glad/include"

include "ThirdParty/GLFW"
include "ThirdParty/Glad"

project "Basic"
  location "Basic"
  kind "StaticLib"
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

  defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

  includedirs
  {
    "%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}"
  }

  links
  {
    "GLFW",
		"Glad",
    "opengl32.lib"
  }

  filter "system:windows"
    systemversion "latest"
    defines
    {
      "GLFW_INCLUDE_NONE"
    }

    filter "configurations:Debug"
  		runtime "Debug"
  		symbols "On"

  	filter "configurations:Release"
  		runtime "Release"
  		optimize "On"

project "Subroutines"
  location "Subroutines"
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++17"
  staticruntime "on"

  targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

  files
  {
    "%{prj.name}/src/**.h",
    "%{prj.name}/src/**.cpp",
  }

  defines
  {
    "GLFW_INCLUDE_NONE"
  }

  includedirs
  {
     "Subroutines/src",
     "Basic/src",
     "%{IncludeDir.Glad}",
     "%{IncludeDir.GLFW}"
  }

  links
  {
      "Basic"
  }

  filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"

--Template for project creation
project "Test"
  location "Test"
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++17"
  staticruntime "on"

  targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

  files
  {
    "%{prj.name}/src/**.h",
    "%{prj.name}/src/**.cpp",
  }

  defines
  {
    "GLFW_INCLUDE_NONE"
  }

  includedirs
  {
     "Test/src",
     "Basic/src",
     "%{IncludeDir.GLFW}",
     "%{IncludeDir.Glad}"
  }

  links
  {
      "Basic"
  }

  filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"
