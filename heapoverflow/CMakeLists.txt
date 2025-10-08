cmake_minimum_required(VERSION 3.16)
project(HOF LANGUAGES CXX C)

# --- Global Settings ---
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set output directories in a standard CMake way (e.g., /bin/Debug, /lib/Release)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<CONFIG>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<CONFIG>)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>)

# Find OpenGL on non-windows systems
if(NOT WIN32)
    find_package(OpenGL REQUIRED)
endif()

# Handle static runtime for MSVC, matching premake's staticruntime "on"
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    # Add compiler options and disable warnings from premake5.lua
    add_compile_options(/W4 /wd4819 /wd4006 /wd26495 /wd4133 /wd4996 /wd4201 /wd26439 /wd4312 /wd26812 /wd4244 /wd4267 /wd4702 /wd4789)
    # Linker option to ignore warning
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /IGNORE:4006")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /IGNORE:4006")
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} /IGNORE:4006")
endif()

# --- Dependency Definitions ---

# Header-only libraries paths
set(GLM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/HOF-Core/Dependencies/glm)
set(ENTT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/HOF-Core/Dependencies/entt/include)
set(TINYOBJ_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/HOF-Core/Dependencies/TinyObjLoader/include)


# --- Dependency Library Targets ---

# GLEW
add_library(GLEW STATIC HOF-Core/Dependencies/GLEW/src/glew.c)
target_include_directories(GLEW PUBLIC HOF-Core/Dependencies/GLEW/include)
target_compile_definitions(GLEW 
    PRIVATE GLEW_STATIC 
    PUBLIC GLEW_NO_GLU
)

# GLFW (Platform-specific build)
file(GLOB GLFW_COMMON_SOURCES
    "HOF-Core/Dependencies/GLFW/src/context.c"
    "HOF-Core/Dependencies/GLFW/src/init.c"
    "HOF-Core/Dependencies/GLFW/src/input.c"
    "HOF-Core/Dependencies/GLFW/src/monitor.c"
    "HOF-Core/Dependencies/GLFW/src/vulkan.c"
    "HOF-Core/Dependencies/GLFW/src/window.c"
    "HOF-Core/Dependencies/GLFW/src/egl_context.c"
    "HOF-Core/Dependencies/GLFW/src/osmesa_context.c"
)

if(WIN32)
    file(GLOB GLFW_PLATFORM_SOURCES
        "HOF-Core/Dependencies/GLFW/src/win32_init.c"
        "HOF-Core/Dependencies/GLFW/src/win32_joystick.c"
        "HOF-Core/Dependencies/GLFW/src/win32_monitor.c"
        "HOF-Core/Dependencies/GLFW/src/win32_thread.c"
        "HOF-Core/Dependencies/GLFW/src/win32_time.c"
        "HOF-Core/Dependencies/GLFW/src/win32_window.c"
        "HOF-Core/Dependencies/GLFW/src/wgl_context.c"
    )
    add_library(GLFW STATIC ${GLFW_COMMON_SOURCES} ${GLFW_PLATFORM_SOURCES})
    target_compile_definitions(GLFW PUBLIC _GLFW_WIN32)
    target_link_libraries(GLFW PRIVATE opengl32 gdi32 user32 shell32)
elseif(APPLE)
    enable_language(OBJC OBJCXX)
    file(GLOB GLFW_PLATFORM_SOURCES
        "HOF-Core/Dependencies/GLFW/src/cocoa_init.m"
        "HOF-Core/Dependencies/GLFW/src/cocoa_joystick.m"
        "HOF-Core/Dependencies/GLFW/src/cocoa_monitor.m"
        "HOF-Core/Dependencies/GLFW/src/cocoa_window.m"
        "HOF-Core/Dependencies/GLFW/src/nsgl_context.m"
        "HOF-Core/Dependencies/GLFW/src/posix_thread.c"
        "HOF-Core/Dependencies/GLFW/src/cocoa_time.c"
    )
    add_library(GLFW STATIC ${GLFW_COMMON_SOURCES} ${GLFW_PLATFORM_SOURCES})
    target_compile_definitions(GLFW PUBLIC _GLFW_COCOA)
    target_link_libraries(GLFW PRIVATE "-framework Cocoa" "-framework IOKit" "-framework CoreFoundation" "-framework OpenGL")
else() # Assuming Linux/X11
    file(GLOB GLFW_PLATFORM_SOURCES
        "HOF-Core/Dependencies/GLFW/src/x11_init.c"
        "HOF-Core/Dependencies/GLFW/src/x11_monitor.c"
        "HOF-Core/Dependencies/GLFW/src/x11_window.c"
        "HOF-Core/Dependencies/GLFW/src/glx_context.c"
        "HOF-Core/Dependencies/GLFW/src/linux_joystick.c"
        "HOF-Core/Dependencies/GLFW/src/posix_thread.c"
        "HOF-Core/Dependencies/GLFW/src/posix_time.c"
        "HOF-Core/Dependencies/GLFW/src/xkb_unicode.c"
    )
    # Find required X11 libraries
    find_package(X11 REQUIRED)
    
    add_library(GLFW STATIC ${GLFW_COMMON_SOURCES} ${GLFW_PLATFORM_SOURCES})
    target_compile_definitions(GLFW PUBLIC _GLFW_X11)
    # Link to X11 and other system libraries
    target_link_libraries(GLFW PRIVATE ${X11_LIBRARIES} pthread dl)
endif()
target_include_directories(GLFW PUBLIC HOF-Core/Dependencies/GLFW/include)


# ImGui (core library)
file(GLOB IMGUI_SOURCES
    "HOF-Core/Dependencies/imgui/imgui.cpp"
    "HOF-Core/Dependencies/imgui/imgui_draw.cpp"
    "HOF-Core/Dependencies/imgui/imgui_widgets.cpp"
    "HOF-Core/Dependencies/imgui/imgui_demo.cpp"
)
add_library(ImGui STATIC ${IMGUI_SOURCES})
target_include_directories(ImGui PUBLIC HOF-Core/Dependencies/imgui)

# TinyObjLoader
add_library(TinyObjLoader STATIC HOF-Core/Dependencies/TinyObjLoader/tiny_obj_loader.cc)
target_include_directories(TinyObjLoader PUBLIC ${TINYOBJ_INCLUDE_DIR})



# --- HOF-Core Project ---
file(GLOB_RECURSE HOF_CORE_SOURCES 
    "HOF-Core/src/**.cpp"
    "HOF-Core/src/**.h"
)
# removefiles from premake
# list(FILTER HOF_CORE_SOURCES EXCLUDE REGEX ".*ObjLoader.cpp")
# list(FILTER HOF_CORE_SOURCES EXCLUDE REGEX ".*ObjLoader.h")



add_library(HOF-Core STATIC ${HOF_CORE_SOURCES})

target_include_directories(HOF-Core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/HOF-Core/src
    $<TARGET_PROPERTY:GLEW,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:GLFW,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:ImGui,INTERFACE_INCLUDE_DIRECTORIES>
    ${GLM_INCLUDE_DIR}
    ${ENTT_INCLUDE_DIR}
    $<TARGET_PROPERTY:TinyObjLoader,INTERFACE_INCLUDE_DIRECTORIES>

)

target_link_libraries(HOF-Core PUBLIC
    GLEW
    GLFW
    ImGui
    TinyObjLoader
)
# Add opengl32 for Windows; for Linux, link against OpenGL::GL
if(WIN32)
    target_link_libraries(HOF-Core PUBLIC opengl32)
else()
    target_link_libraries(HOF-Core PUBLIC OpenGL::GL)
endif()




target_compile_definitions(HOF-Core PUBLIC
    GLFW_INCLUDE_NONE
    GLEW_STATIC
    _CRT_SECURE_NO_WARNINGS
)

# --- Demo Project ---
file(GLOB_RECURSE DEMO_SOURCES "Demo/src/**.cpp" "Demo/src/**.h")
add_executable(Demo ${DEMO_SOURCES})

target_include_directories(Demo PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Demo/src
)

target_link_libraries(Demo PRIVATE HOF-Core)

# Custom target to copy resource files before building the Demo executable
add_custom_target(CopyResources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/Demo/resource"
        "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resource"
    COMMENT "Copying resource files"
)
add_dependencies(Demo CopyResources)


