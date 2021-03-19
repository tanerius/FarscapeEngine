cmake_minimum_required(VERSION 3.18)

message(STATUS "Setting up: sandbox assets version ${FARSCAPE_SANDBOX_ASSET_VER} ...")
set(fs_editor_asset_locations
    "${PROJECT_SOURCE_DIR}/sandbox/assets/editor"
    "${PROJECT_SOURCE_DIR}/sandbox/assets/meshes"
    "${PROJECT_SOURCE_DIR}/sandbox/assets/models"
    "${PROJECT_SOURCE_DIR}/sandbox/assets/shaders"
    "${PROJECT_SOURCE_DIR}/sandbox/assets/textures"
)

congifure_prebuilt_lib (
    "${fs_editor_asset_locations}" 
    "http://home.tanerius.com/libs/assets/Sandbox/Sandbox-${FARSCAPE_SANDBOX_ASSET_VER}.7z" 
    "Sandbox-${FARSCAPE_SANDBOX_ASSET_VER}.7z" 
    "${PROJECT_SOURCE_DIR}/sandbox/assets"
)

