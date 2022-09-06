project "TinyObjLoader"
    kind "StaticLib"
    language "C++"
    staticruntime "on"
    targetdir ("bin/"..outputdir.."/%{prj.name}")
    objdir ("bin-int/"..outputdir.."/%{prj.name}")
    includedirs
    {
        "include"
    }
    files
    {
      "include/tiny_obj_loader.h",
      "tiny_obj_loader.cc",
    }

   filter "system:windows"
      systemversion "latest"
        
   filter "configurations:Debug"
      defines { "DEBUG" } -- -DDEBUG
      runtime "Debug"
      symbols "on"

   filter "configurations:Release"
      runtime "Release"
      optimize "on"