cmake_minimum_required(VERSION 3.18)

# Download and generate the assets structure
add_subdirectory(assets)

# The definitions for the editor
add_executable(FarscapeEditor 
    src/EditorLayer.h
    src/EditorLayer.cpp
    src/EditorApp.cpp
)

# Force this to c++17 
target_compile_features(FarscapeEditor PRIVATE cxx_std_17)

# A command to copy the Assimp DLL to the exe of the editor

get_target_property(FARSCAPE_ASSIMP_DLL Farscape::assimp "assimp_dll")

add_custom_command(TARGET FarscapeEditor POST_BUILD         # Adds a post-build event to MyTest
    COMMAND ${CMAKE_COMMAND} -E copy_if_different           # which executes "cmake - E copy_if_different..."
          ${FARSCAPE_ASSIMP_DLL}                            # <--this is in-file
       $<TARGET_FILE_DIR:FarscapeEditor>                    # <--this is out-file path
)     

# A command to copy the imgui.ini file
add_custom_command(
    TARGET FarscapeEditor POST_BUILD             # Adds a post-build event to MyTest
    COMMAND ${CMAKE_COMMAND} -E copy_if_different               # which executes "cmake - E copy_if_different..."
          ${CMAKE_SOURCE_DIR}/Farscape/configurables/imgui.ini  # <--this is in-file
       $<TARGET_FILE_DIR:FarscapeEditor>                        # <--this is out-file path
) 

# a commad to copy assets 
add_custom_command(TARGET FarscapeEditor POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/Editor/assets 
                       $<TARGET_FILE_DIR:FarscapeEditor>/assets
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