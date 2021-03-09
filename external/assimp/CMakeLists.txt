cmake_minimum_required(VERSION 3.18)

set(fs_assimp_lib_locations
    "${PROJECT_SOURCE_DIR}/External/assimp/include"
    "${PROJECT_SOURCE_DIR}/External/assimp/lib"
    "${PROJECT_SOURCE_DIR}/External/assimp/LICENSE"
)

congifure_prebuilt_lib (
    "${fs_assimp_lib_locations}" 
    "http://home.tanerius.com/libs/assimp/${FARSCAPE_PLATFORM}/vc142/assimp.7z"
    "assimp.7z" 
    "${PROJECT_SOURCE_DIR}/External/assimp"
)

add_library(assimp INTERFACE )

target_include_directories(assimp 
    INTERFACE include/
)

add_library(Farscape::assimp ALIAS assimp)
# $<IF:$<CONFIG:Debug>,"${FARSCAPE_EXTERNALS_DIR}/assimp/lib/Debug/assimp-vc142-mtd.dll","${FARSCAPE_EXTERNALS_DIR}/assimp/lib/Release/assimp-vc142-mt.dll">
# $<IF:$<CONFIG:Debug>,${FARSCAPE_ASSIMP_LIB},${FARSCAPE_ASSIMP_LIB}>


