cmake_minimum_required(VERSION 3.18.1)
project(standoff_mod CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Dobby (Inline Hooking for ARM64) - отключаем ASM
FetchContent_Declare(
    dobby
    GIT_REPOSITORY https://github.com/jmpews/Dobby.git
    GIT_TAG master
)
set(DOBBY_BUILD_ASM_TRAMPOLINE OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(dobby)

# Dear ImGui
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.89.9
)
FetchContent_MakeAvailable(imgui)

file(GLOB IMGUI_SOURCES 
    ${imgui_SOURCE_DIR}/*.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_android.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

add_library(mod SHARED
    src/main.cpp
    src/hooks.cpp
    src/esp.cpp
    src/menu.cpp
    src/il2cpp_resolver.cpp
    ${IMGUI_SOURCES}
)

target_include_directories(mod PRIVATE
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
    ${dobby_SOURCE_DIR}/include
    src/
)

target_link_libraries(mod 
    dobby 
    android 
    log 
    EGL 
    GLESv3 
    OpenSLES
)

target_compile_options(mod PRIVATE -fvisibility=hidden -O2)
