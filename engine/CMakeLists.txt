cmake_minimum_required(VERSION 3.12)

add_library(Farscape SHARED 
	src/Application.cpp
	src/Log.cpp
)

target_include_directories(Farscape 
	PUBLIC include
)

target_link_libraries(Farscape
	PUBLIC spdlog::spdlog
)

target_compile_features(Farscape PRIVATE cxx_std_17)

add_library(Farscape::Farscape ALIAS Farscape)

# define the symbol stating we are using the declspec(dllexport) when
# building on windows
target_compile_definitions(Farscape PRIVATE "FARSCAPE_BUILD_EXPORTS")