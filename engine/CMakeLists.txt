cmake_minimum_required(VERSION 3.12)

# Set the relevant platform dependant sources
if (WIN32)
	set(FS_SPECIFIC_SOURCES 
		"platform/Windows/WindowsWindow.cpp"
		"platform/Windows/WindowsWindow.h"
		"platform/Windows/WindowsInput.cpp"
		"platform/Windows/WindowsInput.h"
	)
elseif (APPLE)
	set(FS_SPECIFIC_SOURCES 
		"platform/Macos/AppleWindow.cpp"
	    "platform/Macos/AppleWindow.h"
	)
endif ()

set(FS_SOURCES 
	pch/fspch.h
	pch/fspch.cpp
	src/Application.cpp
	src/Log.cpp
	src/Layer.cpp
	${FS_SPECIFIC_SOURCES}
	src/Layer.cpp
	src/LayerStack.cpp

	${FS_IMGUI_PATH}/imgui.cpp
	${FS_IMGUI_PATH}/imgui_demo.cpp
	${FS_IMGUI_PATH}/imgui_draw.cpp
	${FS_IMGUI_PATH}/imgui_tables.cpp
	${FS_IMGUI_PATH}/imgui_widgets.cpp
	${FS_IMGUI_PATH}/backends/imgui_impl_opengl3.cpp
	src/ImGuiLayer.cpp
)

# check static vs dynamic
if(FARSCAPE_LINK_STATICALLY)
	add_library(Farscape STATIC 
		${FS_SOURCES}
	)
else()
	add_library(Farscape SHARED 
		${FS_SOURCES}
	)
	# define the symbol stating we are using the declspec(dllexport) when
	# building on windows
	target_compile_definitions(Farscape PRIVATE "FARSCAPE_BUILD_EXPORTS")
endif()

target_compile_definitions(Farscape PUBLIC "_CRT_SECURE_NO_WARNINGS")


target_include_directories(Farscape 
	PUBLIC pch
	PUBLIC include
	PUBLIC ${FS_IMGUI_PATH}
	PUBLIC ${FS_IMGUI_PATH}/backends
	PUBLIC glm::glm
)

add_precompiled_header(Farscape fspch.h SOURCE_CXX pch/fspch.cpp FORCEINCLUDE)

target_link_libraries(Farscape
	PUBLIC spdlog::spdlog
	PUBLIC glfw
	PUBLIC Farscape::glad
)

target_compile_features(Farscape PRIVATE cxx_std_17)

if(MSVC)
  target_compile_options(Farscape PRIVATE /W4 /WX)
else()
  target_compile_options(Farscape PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

add_library(Farscape::Farscape ALIAS Farscape)



install(TARGETS Farscape
	CONFIGURATIONS Debug
	DESTINATION "${FARSCAPE_BINARY_DIR}/Debug"
)

install(TARGETS Farscape
	CONFIGURATIONS Release
	DESTINATION "${FARSCAPE_BINARY_DIR}/Release"
)