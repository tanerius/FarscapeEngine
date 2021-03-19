cmake_minimum_required(VERSION 3.18)

message(STATUS "Setting up: editor assets version ${FARSCAPE_EDITOR_ASSET_VER} ...")
set(fs_editor_asset_locations
    "${PROJECT_SOURCE_DIR}/Editor/assets/editor"
    "${PROJECT_SOURCE_DIR}/Editor/assets/env"
    "${PROJECT_SOURCE_DIR}/Editor/assets/meshes"
    "${PROJECT_SOURCE_DIR}/Editor/assets/models"
    "${PROJECT_SOURCE_DIR}/Editor/assets/shaders"
    "${PROJECT_SOURCE_DIR}/Editor/assets/textures"
)

congifure_prebuilt_lib (
    "${fs_editor_asset_locations}" 
    "http://home.tanerius.com/libs/assets/Editor/Editor-${FARSCAPE_EDITOR_ASSET_VER}.7z" 
    "Editor-${FARSCAPE_EDITOR_ASSET_VER}.7z" 
    "${PROJECT_SOURCE_DIR}/Editor/assets"
)

