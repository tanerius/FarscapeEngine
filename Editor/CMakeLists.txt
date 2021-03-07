cmake_minimum_required(VERSION 3.12)

add_executable(FarscapeEditor 
    src/EditorLayer.h
    src/EditorLayer.cpp
    src/EditorApp.cpp
)

target_link_libraries(FarscapeEditor
    PRIVATE Farscape::Farscape
)

install(TARGETS FarscapeEditor
    CONFIGURATIONS Debug
    DESTINATION "${FARSCAPE_BINARY_DIR}/Debug"
)

install(TARGETS FarscapeEditor
    CONFIGURATIONS Release
    DESTINATION "${FARSCAPE_BINARY_DIR}/Release"
)