cmake_minimum_required(VERSION 3.18)

project(Farscape 
    VERSION 1.0.0
    DESCRIPTION "Farscape game engine project"
    LANGUAGES CXX C
)

# include support for pre 3.16 precompiled header support
include(cmake_modules/PrecompiledHeader.cmake)
# include helpers
include(cmake_modules/Helpers.cmake)

#First set the platform and global parameters
set_farscape_platform()
set_farscape_globals()

# TODO: DON'T USE GLOBALS LIKE AN ASSHOLE
set(CMAKE_CXX_STANDARD 17)
OPTION(FARSCAPE_LINK_STATICALLY "Engine static library" On)
OPTION(FARSCAPE_DEBUG "Enable debugging logs and asserts" On)

# Set some super global stuff here
if (FARSCAPE_PLATFORM STREQUAL "Win64")
	if( CONFIG_TYPE STREQUAL "Debug")
		message(STATUS "*** Build type is:				DEBUG")
		set(FARSCAPE_ASSIMP_LIB "${FARSCAPE_EXTERNALS_DIR}/assimp/lib/Debug/assimp-vc142-mtd.lib")
		set(FARSCAPE_ASSIMP_DLL "${FARSCAPE_EXTERNALS_DIR}/assimp/lib/Debug/assimp-vc142-mtd.dll")
	else()
		message(STATUS "*** Build type is:				RELEASE")
		set(FARSCAPE_ASSIMP_LIB "${FARSCAPE_EXTERNALS_DIR}/assimp/lib/Release/assimp-vc142-mt.lib")
		set(FARSCAPE_ASSIMP_DLL "${FARSCAPE_EXTERNALS_DIR}/assimp/lib/Release/assimp-vc142-mt.dll")
	endif()
else()
	message(FATAL_ERROR "STOP! Non Win64 platform is currently not supported")
endif()

configure_file(Farscape/configurables/versions.h.in ${FARSCAPE_BINARY_DIR}/generated/Versions.h @ONLY)

#print the configuration 
print_farscape_environment()

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