cmake_minimum_required(VERSION 3.18)

add_library(fsglad STATIC 
		src/glad.c
	)

target_include_directories(fsglad 
	PUBLIC include
)

add_library(Farscape::glad ALIAS fsglad)