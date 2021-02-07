cmake_minimum_required(VERSION 3.12)

project(Farscape 
    VERSION 1.0.0
    DESCRIPTION "Farscape game engine project"
    LANGUAGES CXX
)

# Set some super global stuff here
message(STATUS "Setting directories...")
set(FARSCAPE_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/out")
set(FARSCAPE_EXTERNAL_DIR "${CMAKE_SOURCE_DIR}/external")

set(FARSCAPE_BINARY_DIR "${FARSCAPE_OUTPUT_DIR}/bin")
set(FARSCAPE_BUILD_DIR "${FARSCAPE_OUTPUT_DIR}/build")
set(FARSCAPE_INTERMEDIATE_DIR "${FARSCAPE_OUTPUT_DIR}/intermediate")
set(FARSCAPE_INSTALL_DIR "${FARSCAPE_OUTPUT_DIR}/install")

message(STATUS "FARSCAPE_OUTPUT_DIR          ${FARSCAPE_OUTPUT_DIR}")
message(STATUS "FARSCAPE_EXTERNAL_DIR        ${FARSCAPE_EXTERNAL_DIR}")
message(STATUS "FARSCAPE_BINARY_DIR          ${FARSCAPE_BINARY_DIR}")
message(STATUS "FARSCAPE_INTERMEDIATE_DIR    ${FARSCAPE_INTERMEDIATE_DIR}")
message(STATUS "FARSCAPE_INSTALL_DIR         ${FARSCAPE_INSTALL_DIR}")
message(STATUS "CMAKE_BINARY_DIR             ${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE_INSTALL_PREFIX         ${CMAKE_INSTALL_PREFIX}")


# add all required externals
#add_subdirectory(external)
# add engine sources
#add_subdirectory(engine)
# add sandbox sources
#add_subdirectory(sandbox)
