cmake_minimum_required(VERSION 3.12)

add_executable(Sandbox 
	src/main.cpp
)

target_link_libraries(Sandbox
	PRIVATE Farscape::Farscape
)

install(TARGETS Sandbox
	CONFIGURATIONS Debug
	DESTINATION "${FARSCAPE_BINARY_DIR}/Debug"
)

install(TARGETS Sandbox
	CONFIGURATIONS Release
	DESTINATION "${FARSCAPE_BINARY_DIR}/Release"
)