workspace "HOF"
    
    startproject "HOF"
    
    platforms { "x64" }
    configurations
    {
        "Debug",
        "Release"
    }

outputdir="%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir={}
IncludeDir["Core"]="HOF-Core/src"
IncludeDir["GLEW"]="HOF-Core/Dependencies/GLEW/include"
IncludeDir["GLFW"]="HOF-Core/Dependencies/GLFW/include"
IncludeDir["imgui"]="HOF-Core/Dependencies/imgui"
IncludeDir["glm"]="HOF-Core/Dependencies/glm"
IncludeDir["entt"] = "HOF-Core/Dependencies/entt/include"
IncludeDir["TinyObjLoader"] = "HOF-Core/Dependencies/TinyObjLoader/include"
IncludeDir["Assimp"] = "HOF-Core/Dependencies/assimp/include"

group "Dependencies"
    include "HOF-Core/Dependencies/GLEW"
    include "HOF-Core/Dependencies/GLFW"
    include "HOF-Core/Dependencies/imgui"
    include "HOF-Core/Dependencies/TinyObjLoader"
group ""

project "HOF-Core"
    location "HOF-Core"
    kind "StaticLib"
    language "C++"
    cppdialect "c++17"
    staticruntime "on"
    warnings "Extra"

    targetdir ("bin/"..outputdir.."/%{prj.name}")
    objdir("bin-int/"..outputdir.."/%{prj.name}")


    
    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/Dependencies/glm/glm/**.hpp",
        "%{prj.name}/Dependencies/glm/glm/**.inl",
        "%{prj.name}/Dependencies/entt/include/**.hpp",
    }
    removefiles 
    { 
        "%{prj.name}/src/Core/Utils/ObjLoader.cpp",
        "%{prj.name}/src/Core/Utils/ObjLoader.h",
    }

    includedirs
    {
        "%{IncludeDir.Core}",
        "%{IncludeDir.GLEW}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.imgui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.entt}",
        "%{IncludeDir.TinyObjLoader}",
        "%{IncludeDir.Assimp}"
    }

    links
    {
        "GLEW",
        "GLFW",
        "ImGui",
        "TinyObjLoader",
        "opengl32.lib"
    }
    defines
    {
        "GLFW_INCLUDE_NONE",
        "GLEW_STATIC",
        "_CRT_SECURE_NO_WARNINGS"
    }
    disablewarnings { "4819", "4006","26495","4133","4996","4201","26439","4312","26812","4244","4267","4702","4789" }
    linkoptions { "-IGNORE:4006" }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

        links
        {
            "HOF-Core/Dependencies/assimp/Debug/assimp-vc142-mtd.lib"
        }


    filter "configurations:Release"
        runtime "Release"
        optimize "on"

        links
        {
            "HOF-Core/Dependencies/assimp/Release/assimp-vc142-mt.lib"
        }


project "Demo"
    location "Demo"
    kind "consoleApp"
    language "C++"
    cppdialect "c++17"
    staticruntime "on"
    warnings "Extra"

    targetdir ("bin/"..outputdir.."/%{prj.name}")
    objdir("bin-int/"..outputdir.."/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src/",
        "%{IncludeDir.Core}",
        "%{IncludeDir.GLEW}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.imgui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.entt}",
        "%{IncludeDir.TinyObjLoader}"
    }

    links
    {
        "HOF-Core",
        
    }
    defines
    {
        "GLFW_INCLUDE_NONE",
        "GLEW_STATIC",
        "_CRT_SECURE_NO_WARNINGS"
    }
    disablewarnings { "4819", "4006","26495","4133","4996","4201","26439","4312","26812","4244","4267","4702","4789" }
    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"
        postbuildcommands 
		{
            ('xcopy "../Demo/resource" "%{cfg.targetdir}/resource" /e /h /k /y /i'),
			('{COPY} "../HOF-Core/Dependencies/assimp/Debug/assimp-vc142-mtd.dll" "%{cfg.targetdir}"')
		}

    filter "configurations:Release"
        runtime "Release"
        optimize "on"

        postbuildcommands 
		{
            ('xcopy "../Demo/resource" "%{cfg.targetdir}/resource" /e /h /k /y /i'),
			('{COPY} "../HOF-Core/Dependencies/assimp/Release/assimp-vc142-mt.dll" "%{cfg.targetdir}"')
		}


