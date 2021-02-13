cmake_minimum_required(VERSION 3.12)

add_library(Farscape SHARED 
	pch/fspch.h
	pch/fspch.cpp
	src/Application.cpp
	src/Log.cpp
)

target_include_directories(Farscape 
	PUBLIC include
	PUBLIC pch
)

add_precompiled_header(Farscape fspch.h SOURCE_CXX pch/fspch.cpp FORCEINCLUDE)

target_link_libraries(Farscape
	PUBLIC spdlog::spdlog
	PUBLIC glfw
)

target_compile_features(Farscape PRIVATE cxx_std_17)

if(MSVC)
  target_compile_options(Farscape PRIVATE /W4 /WX)
else()
  target_compile_options(Farscape PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

add_library(Farscape::Farscape ALIAS Farscape)

# define the symbol stating we are using the declspec(dllexport) when
# building on windows
target_compile_definitions(Farscape PRIVATE "FARSCAPE_BUILD_EXPORTS")

install(TARGETS Farscape
	CONFIGURATIONS Debug
	DESTINATION "${FARSCAPE_BINARY_DIR}/Debug"
)

install(TARGETS Farscape
	CONFIGURATIONS Release
	DESTINATION "${FARSCAPE_BINARY_DIR}/Release"
)