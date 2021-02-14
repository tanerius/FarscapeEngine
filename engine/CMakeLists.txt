cmake_minimum_required(VERSION 3.12)

# Find opengl
find_package(OpenGL REQUIRED)
if( NOT OpenGL_FOUND )
	message(FATAL_ERROR "OpenGL Not found")
endif()


# Set the relevant platform
if (WIN32)
	set(WINDOW_HANDLER_SRC "platform/Windows/WindowsWindow.cpp")
	set(WINDOW_HANDLER_HDR "platform/Windows/WindowsWindow.h")
endif (WIN32)

add_library(Farscape SHARED 
	pch/fspch.h
	pch/fspch.cpp
	src/Application.cpp
	src/Log.cpp
	${WINDOW_HANDLER_HDR}
	${WINDOW_HANDLER_SRC}
)

target_include_directories(Farscape 
	PUBLIC include
	PUBLIC pch
	PUBLIC ${OPENGL_INCLUDE_DIRS}
)

add_precompiled_header(Farscape fspch.h SOURCE_CXX pch/fspch.cpp FORCEINCLUDE)

target_link_libraries(Farscape
	PUBLIC spdlog::spdlog
	PUBLIC glfw
	PUBLIC ${OPENGL_LIBRARIES}
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