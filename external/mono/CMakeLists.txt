cmake_minimum_required(VERSION 3.18)

message(STATUS "Setting up: mono")
set(fs_mono_lib_locations
    "${PROJECT_SOURCE_DIR}/External/mono/bin"
    "${PROJECT_SOURCE_DIR}/External/mono/include"
    "${PROJECT_SOURCE_DIR}/External/mono/lib"
    "${PROJECT_SOURCE_DIR}/External/mono/lib/Release"
)

congifure_prebuilt_lib (
    "${fs_mono_lib_locations}" 
    "http://home.tanerius.com/libs/mono/${FARSCAPE_PLATFORM}/mono.7z" 
    "mono.7z" 
    "${PROJECT_SOURCE_DIR}/External/mono"
)


add_library(mono INTERFACE )

target_include_directories(assimp 
    INTERFACE include/
)

add_library(Farscape::mono ALIAS mono)