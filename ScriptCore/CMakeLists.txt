cmake_minimum_required(VERSION 3.18)

project(ScriptCore VERSION 0.0.1 LANGUAGES CSharp)

# Glob the the renderer API sources
file(GLOB_RECURSE FS_SCRIPTCORE_SOURCES
            LIST_DIRECTORIES false 
            src/*
        )

add_library(ScriptCore SHARED 
		${FS_SCRIPTCORE_SOURCES}
	)

if( CONFIG_TYPE STREQUAL "Debug")
	set_target_properties(ScriptCore PROPERTIES COMPILE_DEFINITIONS "DEBUG")
endif()


add_library(Farscape::ScriptCore ALIAS ScriptCore)