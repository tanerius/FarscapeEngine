cmake_minimum_required(VERSION 3.12)

project(Farscape 
    VERSION 1.0.0
    DESCRIPTION "Farscape game engine project"
    LANGUAGES CXX C
)

set(CMAKE_CXX_STANDARD 17)

option(FARSCAPE_LINK_STATICALLY "Engine static library" On)
OPTION(FARSCAPE_DEBUG "Enable debugging logs and asserts" On)



# Set some super global stuff here
message(STATUS "Setting directories...")
set(FARSCAPE_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/out")

set(FARSCAPE_BINARY_DIR "${FARSCAPE_OUTPUT_DIR}/bin")
set(FARSCAPE_BUILD_DIR "${FARSCAPE_OUTPUT_DIR}/build")
set(FARSCAPE_INTERMEDIATE_DIR "${FARSCAPE_OUTPUT_DIR}/intermediate")
set(FARSCAPE_INSTALL_DIR "${FARSCAPE_OUTPUT_DIR}/install")
set(FARSCAPE_EXTERNALS_DIR "${CMAKE_SOURCE_DIR}/external")

string(TIMESTAMP BUILD_DATE "%Y-%m-%d %H:%M" UTC)

# TODO : Do this only in debug!!!!
if( CONFIG_TYPE STREQUAL "Debug")
	message(STATUS "*** Build type is:				DEBUG")
	set(EDITOR_ASSETS_PATH "${CMAKE_SOURCE_DIR}/Editor/assets")
	set(EDITOR_MASTER_PATH "${CMAKE_SOURCE_DIR}/Editor/master")
	set(ASSETS_PATH ${EDITOR_ASSETS_PATH})
	set(FARSCAPE_ASSIMP_LIB "${FARSCAPE_EXTERNALS_DIR}/assimp/lib/Debug/assimp-vc142-mtd.lib")
	set(FARSCAPE_ASSIMP_DLL "${FARSCAPE_EXTERNALS_DIR}/assimp/lib/Debug/assimp-vc142-mtd.dll")
else()
	message(STATUS "*** Build type is:				RELEASE")
	set(EDITOR_ASSETS_PATH "assets")
	set(EDITOR_MASTER_PATH "master")
	set(ASSETS_PATH "assets")
	set(FARSCAPE_ASSIMP_LIB "${FARSCAPE_EXTERNALS_DIR}/assimp/lib/Release/assimp-vc142-mt.lib")
	set(FARSCAPE_ASSIMP_DLL "${FARSCAPE_EXTERNALS_DIR}/assimp/lib/Release/assimp-vc142-mt.dll")
endif()

if(FARSCAPE_LINK_STATICALLY)
	message(STATUS "Farscape linking type				STATIC ")
	add_definitions(-DFARSCAPE_STATIC)
else()
	message(STATUS "Farscape linking type				DYNAMIC ")
endif()
message(STATUS "FARSCAPE_OUTPUT_DIR				${FARSCAPE_OUTPUT_DIR}")
message(STATUS "FARSCAPE_BINARY_DIR				${FARSCAPE_BINARY_DIR}")
message(STATUS "FARSCAPE_INTERMEDIATE_DIR			${FARSCAPE_INTERMEDIATE_DIR}")
message(STATUS "FARSCAPE_INSTALL_DIR				${FARSCAPE_INSTALL_DIR}")
message(STATUS "CMAKE_BINARY_DIR					${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE_INSTALL_PREFIX				${CMAKE_INSTALL_PREFIX}")
message(STATUS "FARSCAPE_EXTERNALS_DIR			${FARSCAPE_EXTERNALS_DIR}")
message(STATUS "FARSCAPE_ASSIMP_LIB				${FARSCAPE_ASSIMP_LIB}")
message(STATUS "FARSCAPE_ASSIMP_DLL				${FARSCAPE_ASSIMP_DLL}")
message(STATUS "ASSETS_PATH						${ASSETS_PATH}")
message(STATUS "EDITOR_ASSETS_PATH				${EDITOR_ASSETS_PATH}")

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

# add Editor sources
add_subdirectory(Editor)