cmake_minimum_required(VERSION 3.18)

# Add the assets for sandbox
add_subdirectory(assets)

add_executable(Sandbox 
    "src/Sandbox.cpp")

# Farscape engine if c++17
target_compile_features(Sandbox PRIVATE cxx_std_17)

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