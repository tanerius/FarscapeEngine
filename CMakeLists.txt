cmake_minimum_required(VERSION 3.18)

project(Farscape 
    VERSION 1.0.0
    DESCRIPTION "Farscape game engine project"
    LANGUAGES CXX C
)

set(FARSCAPE_EDITOR_ASSET_VER "1.0.0")
set(FARSCAPE_SANDBOX_ASSET_VER "1.0.0")

# include support for pre 3.16 precompiled header support
include(cmake_modules/PrecompiledHeader.cmake)
# include helpers
include(cmake_modules/Helpers.cmake)

#First set the platform and global parameters
set_farscape_platform()
set_farscape_globals()

OPTION(FARSCAPE_LINK_STATICALLY "Engine static library" On)
OPTION(FARSCAPE_DEBUG "Enable debugging logs and asserts" On)

# Set some super global stuff here
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