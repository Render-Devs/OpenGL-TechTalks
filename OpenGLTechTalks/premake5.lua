workspace "OpenGLTechTalks"
  architecture "x64"

  configurations
  {
    "Debug",
    "Release"
  }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "ThirdParty/GLFW/include"
IncludeDir["Glad"] = "ThirdParty/Glad/include"
IncludeDir["glm"] = "ThirdParty/glm"

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
    "%{prj.name}/src/**.cpp",
    "ThirdParty/glm/glm/**.hpp",
    "ThirdParty/glm/glm/**.inl"
  }

  defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

  includedirs
  {
    "%{IncludeDir.GLFW}",
    "%{IncludeDir.Glad}",
    "%{IncludeDir.glm}"
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

project "DrawArrays"
  location "DrawArrays"
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

  includedirs
  {
    "DrawArrays/src",
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

project "MultiDrawArrays"
  location "MultiDrawArrays"
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

  includedirs
  {
    "MultiDrawArrays/src",
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

project "DrawElements"
  location "DrawElements"
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

  includedirs
  {
    "DrawElements/src",
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

project "MultiDrawElements"
  location "MultiDrawElements"
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

  includedirs
  {
    "MultiDrawElements/src",
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
        
project "DrawElementsBase"
  location "DrawElementsBase"
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

  includedirs
  {
    "DrawElementsBase/src",
    "Basic/src",
    "%{IncludeDir.GLFW}",    
    "%{IncludeDir.Glad}",    
    "%{IncludeDir.glm}"
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
        
project "Uniforms"
  location "Uniforms"
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

  includedirs
  {
    "DrawElementsBase/src",
    "Basic/src",
    "%{IncludeDir.GLFW}",    
    "%{IncludeDir.Glad}",    
    "%{IncludeDir.glm}"
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

project "SimpleMultisampling"
  location "SimpleMultisampling"
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

  includedirs
  {
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
