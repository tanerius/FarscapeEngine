cmake_minimum_required(VERSION 3.12)

add_library(assimp INTERFACE )

target_include_directories(assimp 
    INTERFACE include/
)

add_library(Farscape::assimp ALIAS assimp)
# $<IF:$<CONFIG:Debug>,"${FARSCAPE_EXTERNALS_DIR}/assimp/lib/Debug/assimp-vc142-mtd.dll","${FARSCAPE_EXTERNALS_DIR}/assimp/lib/Release/assimp-vc142-mt.dll">
# $<IF:$<CONFIG:Debug>,${FARSCAPE_ASSIMP_LIB},${FARSCAPE_ASSIMP_LIB}>


