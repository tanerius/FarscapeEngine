cmake_minimum_required(VERSION 3.12)

add_library(Farscape SHARED 
	src/Application.cpp
)

target_include_directories(Farscape 
	PUBLIC include
)

add_library(Farscape::Engine ALIAS Farscape)

# define the symbol stating we are using the declspec(dllexport) when
# building on windows
target_compile_definitions(Farscape PRIVATE "FARSCAPE_BUILD_EXPORTS")