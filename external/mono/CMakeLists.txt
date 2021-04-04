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

target_include_directories(mono 
    INTERFACE include/
)

if (FARSCAPE_PLATFORM STREQUAL "Win64")
	if( CONFIG_TYPE STREQUAL "Debug")
		set(tmp_lib "${PROJECT_SOURCE_DIR}/External/mono/lib/Debug/mono-2.0-sgen.lib")
	else()
		set(tmp_lib "${PROJECT_SOURCE_DIR}/External/mono/lib/Release/mono-2.0-sgen.lib")
	endif()
else()
	message(FATAL_ERROR "STOP! Non Win64 platform is currently not supported")
endif()

set_target_properties(mono PROPERTIES 
                        "mono_sgen_lib" ${tmp_lib}
                        "mono_lib_folder" "${PROJECT_SOURCE_DIR}/External/mono/lib"
                      )

add_library(Farscape::mono ALIAS mono)
