cmake_minimum_required(VERSION 3.18)

message(STATUS "Setting up: assimp")

if (FARSCAPE_PLATFORM STREQUAL "Win64")
	if( CONFIG_TYPE STREQUAL "Debug")
		set(tmp_lib "${FARSCAPE_EXTERNALS_DIR}/assimp/lib/Debug/assimp-vc142-mtd.lib")
		set(tmp_dll "${FARSCAPE_EXTERNALS_DIR}/assimp/lib/Debug/assimp-vc142-mtd.dll")
	else()
		set(tmp_lib "${FARSCAPE_EXTERNALS_DIR}/assimp/lib/Release/assimp-vc142-mt.lib")
		set(tmp_dll "${FARSCAPE_EXTERNALS_DIR}/assimp/lib/Release/assimp-vc142-mt.dll")
	endif()
else()
	message(FATAL_ERROR "STOP! Non Win64 platform is currently not supported")
endif()

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


set_target_properties(assimp
                      PROPERTIES "assimp_library" "${tmp_lib}"
					  "assimp_dll" "${tmp_dll}"
                      )


add_library(Farscape::assimp ALIAS assimp)

install(FILES "${tmp_dll}"
    CONFIGURATIONS Debug
    DESTINATION "${FARSCAPE_BINARY_DIR}/Debug"
)

install(FILES "${tmp_dll}"
    CONFIGURATIONS Release
    DESTINATION "${FARSCAPE_BINARY_DIR}/Release"
)

# $<IF:$<CONFIG:Debug>,"${FARSCAPE_EXTERNALS_DIR}/assimp/lib/Debug/assimp-vc142-mtd.dll","${FARSCAPE_EXTERNALS_DIR}/assimp/lib/Release/assimp-vc142-mt.dll">
# $<IF:$<CONFIG:Debug>,${FARSCAPE_ASSIMP_LIB},${FARSCAPE_ASSIMP_LIB}>


