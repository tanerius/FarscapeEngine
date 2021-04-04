cmake_minimum_required(VERSION 3.18)

add_subdirectory(libs)

set(FS_ENGINE_SRC_PATH "src/Farscape/Engine")
set(FS_PLATFORM_SPECIFIC_SRC_PATH "src/Farscape/Platform/OS")
set(FS_RENDERER_SPECIFIC_SRC_PATH "src/Farscape/Platform/Video")

if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    set(BUILD_SHARED_LIBS TRUE)
endif()

# Probablu the ONLY good way to use GLOB without leaking out of targets
# Glob the core engine dsources
file(GLOB_RECURSE FS_SOURCES_ENGINE
            LIST_DIRECTORIES false 
            ${FS_ENGINE_SRC_PATH}/*
        )

# Glob the the renderer API sources
file(GLOB_RECURSE FS_SOURCES_RENDERERS
            LIST_DIRECTORIES false 
            ${FS_RENDERER_SPECIFIC_SRC_PATH}/*
        )

# Glob the OS specific stuff
if(${FARSCAPE_PLATFORM} STREQUAL "Win64")
    # These sources are included only if the OS is a 64 bit windows 
    set(FS_SOURCES_OS
        "${FS_PLATFORM_SPECIFIC_SRC_PATH}/Windows/WindowsWindow.cpp"
        "${FS_PLATFORM_SPECIFIC_SRC_PATH}/Windows/WindowsWindow.h"
        "${FS_PLATFORM_SPECIFIC_SRC_PATH}/Windows/WindowsInput.cpp"
    )
elseif (${FARSCAPE_PLATFORM} STREQUAL "Apple")
    # These sources are included if the OS is MacOS
    set(FS_SOURCES_OS 
        "${FS_PLATFORM_SPECIFIC_SRC_PATH}/Macos/AppleWindow.cpp"
        "${FS_PLATFORM_SPECIFIC_SRC_PATH}/Macos/AppleWindow.h"
    )
else()
    message(FATAL_ERROR "OS not supported")
endif ()

# Put it all together starting from PCH
set(FS_SOURCES 
    "src/pch/fspch.h"
    "src/pch/fspch.cpp"
    ${FS_SOURCES_ENGINE}
    ${FS_SOURCES_RENDERERS}
    ${FS_SOURCES_OS}
)


 # OpenGL
find_package(OpenGL REQUIRED)

# check static vs dynamic
if(FARSCAPE_LINK_STATICALLY)
    add_library(Farscape STATIC 
        ${FS_SOURCES}
 )
else()
    add_library(Farscape SHARED 
        ${FS_SOURCES}
    )
    # define the symbol stating we are using the declspec(dllexport) when
    # building on windows
    target_compile_definitions(Farscape PRIVATE "FARSCAPE_BUILD_EXPORTS")
endif()

# Farscape engine if c++17
target_compile_features(Farscape PRIVATE cxx_std_17)

target_compile_definitions(Farscape 
    PUBLIC "_CRT_SECURE_NO_WARNINGS"
)
# TODO: REMOVE THIS OR PUT IN DEBUG
target_compile_definitions(Farscape PUBLIC "FS_DEBUG")


target_include_directories(Farscape 
    PUBLIC src/pch
    PUBLIC src/include
    PUBLIC src/Farscape/Engine
    PUBLIC src/Farscape/Platform
    PUBLIC ${FARSCAPE_BINARY_DIR}/generated
    PUBLIC ${OPENGL_INCLUDE_DIRS}
)

add_precompiled_header(Farscape fspch.h SOURCE_CXX src/pch/fspch.cpp FORCEINCLUDE)
get_target_property(FARSCAPE_ASSIMP_LIB Farscape::assimp "assimp_library")
get_target_property(FARSCAPE_MONO_LIB Farscape::mono "mono_sgen_lib")

target_link_libraries(Farscape
    PUBLIC spdlog::spdlog
    PUBLIC Farscape::imgui_gl3glfw
    PUBLIC glfw
    PUBLIC Farscape::glad
    PUBLIC glm::glm
    PUBLIC Farscape::stb
    PUBLIC Farscape::assimp
    ${OPENGL_LIBRARIES}
    PUBLIC ${FARSCAPE_ASSIMP_LIB}
    PUBLIC Farscape::entt
    PUBLIC Farscape::FastNoiseLite
    PUBLIC Farscape::mono
    PUBLIC ${FARSCAPE_MONO_LIB}
)

if(MSVC)
  target_compile_options(Farscape PRIVATE /W4 /WX)
else()
  target_compile_options(Farscape PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

add_library(Farscape::Farscape ALIAS Farscape)

install(TARGETS Farscape
    CONFIGURATIONS Debug
    DESTINATION "${FARSCAPE_BINARY_DIR}/Debug"
)

install(TARGETS Farscape
    CONFIGURATIONS Release
    DESTINATION "${FARSCAPE_BINARY_DIR}/Release"
)

install(FILES "configurables/imgui.ini"
    CONFIGURATIONS Debug
    DESTINATION "${FARSCAPE_BINARY_DIR}/Debug"
)

install(FILES "configurables/imgui.ini"
    CONFIGURATIONS Release
    DESTINATION "${FARSCAPE_BINARY_DIR}/Release"
)