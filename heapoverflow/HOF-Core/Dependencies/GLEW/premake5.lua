project "GLEW"
    kind "StaticLib"
    language "C"
    staticruntime "on"
    targetdir ("bin/"..outputdir.."/%{prj.name}")
    objdir ("bin-int/"..outputdir.."/%{prj.name}")
    includedirs
    {
        "include"
    }
    files
    {
        "src/**.c",
        "include/**"
    }
    defines
    {
        "WIN32",
        "GLEW_STATIC",
        "_CRT_SECURE_NO_WARNINGS"
    }
    disablewarnings { "4819", "4006","26495","4133","4996","4201","26439","4312","26812","4244","4267","4702" }
    linkoptions { "-IGNORE:4006" }
    filter "system:windows"
        systemversion "latest"
        
    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"