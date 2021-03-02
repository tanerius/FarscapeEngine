cmake_minimum_required(VERSION 3.12)

project(Farscape 
    VERSION 1.0.0
    DESCRIPTION "Farscape game engine project"
    LANGUAGES CXX C
)

set(CMAKE_CXX_STANDARD 17)

option(FARSCAPE_LINK_STATICALLY "Engine static library" On)

if(FARSCAPE_LINK_STATICALLY)
	message(STATUS "Farscape * Static linking")
	add_definitions(-DFARSCAPE_STATIC)
endif()

# Set some super global stuff here
message(STATUS "Setting directories...")
set(FARSCAPE_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/out")

set(FARSCAPE_BINARY_DIR "${FARSCAPE_OUTPUT_DIR}/bin")
set(FARSCAPE_BUILD_DIR "${FARSCAPE_OUTPUT_DIR}/build")
set(FARSCAPE_INTERMEDIATE_DIR "${FARSCAPE_OUTPUT_DIR}/intermediate")
set(FARSCAPE_INSTALL_DIR "${FARSCAPE_OUTPUT_DIR}/install")

message(STATUS "FARSCAPE_OUTPUT_DIR          ${FARSCAPE_OUTPUT_DIR}")
message(STATUS "FARSCAPE_BINARY_DIR          ${FARSCAPE_BINARY_DIR}")
message(STATUS "FARSCAPE_INTERMEDIATE_DIR    ${FARSCAPE_INTERMEDIATE_DIR}")
message(STATUS "FARSCAPE_INSTALL_DIR         ${FARSCAPE_INSTALL_DIR}")
message(STATUS "CMAKE_BINARY_DIR             ${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE_INSTALL_PREFIX         ${CMAKE_INSTALL_PREFIX}")


string(TIMESTAMP BUILD_DATE "%Y-%m-%d %H:%M" UTC)

# TODO : Do this only in debug!!!!
set(DEBUG_ASSETS_PATH "${CMAKE_SOURCE_DIR}/Sandbox/assets")
set(DEBUG_SHADER_PATH "${DEBUG_ASSETS_PATH}/Shaders/Texture.glsl")
set(DEBUG_TEXTURE_PATH "${CMAKE_SOURCE_DIR}/Sandbox/assets/textures/Checkerboard.png")
set(DEBUG_TEXTURE_RGBA_PATH "${CMAKE_SOURCE_DIR}/Sandbox/assets/textures/rgba.png")

set(ASSETS_PATH ${DEBUG_ASSETS_PATH})

configure_file(Farscape/configurables/versions.h.in ${FARSCAPE_BINARY_DIR}/generated/Versions.h @ONLY)

# include support for pre 3.16 precompiled header support
include(cmake_modules/PrecompiledHeader.cmake)

#[[
# Include Needed packages
# Enables ${OPENGL_INCLUDE_DIRS} and ${OPENGL_LIBRARIES}
find_package(OpenGL REQUIRED)
if( NOT OpenGL_FOUND )
	message(FATAL_ERROR "OpenGL Not found")
endif()
]]


# add all required externals
add_subdirectory(External)

# add shared
add_subdirectory(Shared)

# add engine sources
add_subdirectory(Farscape)

# add sandbox sources
add_subdirectory(Sandbox)
