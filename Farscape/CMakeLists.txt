cmake_minimum_required(VERSION 3.12)

add_subdirectory(libs)

# Set the relevant platform dependant sources
if (WIN32)
    set(FS_SPECIFIC_SOURCES 
        "src/platform/Windows/WindowsWindow.cpp"
        "src/platform/Windows/WindowsWindow.h"
        "src/platform/Windows/WindowsInput.cpp"
        "src/platform/Windows/WindowsInput.h"
        "src/platform/Windows/OpenGLContext.cpp"
        "src/platform/Windows/OpenGLContext.h"
        "src/platform/Windows/OpenGLBuffer.cpp"
        "src/platform/Windows/OpenGLBuffer.h"
        "src/platform/Windows/OpenGLVertexArray.h"
        "src/platform/Windows/OpenGLVertexArray.cpp"
        "src/platform/Windows/OpenGLRendererAPI.h"
        "src/platform/Windows/OpenGLRendererAPI.cpp"
        "src/platform/Windows/OpenGLShader.h"
        "src/platform/Windows/OpenGLShader.cpp"
        "src/platform/Windows/OpenGLTexture.h"
        "src/platform/Windows/OpenGLTexture.cpp"
    )
elseif (APPLE)
    set(FS_SPECIFIC_SOURCES 
        "src/platform/Macos/AppleWindow.cpp"
        "src/platform/Macos/AppleWindow.h"
    )
endif ()


set(FS_SOURCES 
    src/pch/fspch.h
    src/pch/fspch.cpp
    src/private/Application.cpp
    src/private/Log.cpp
    src/private/Core.cpp
    src/private/Layer.cpp
    ${FS_SPECIFIC_SOURCES}
    src/private/Layer.cpp
    src/private/LayerStack.cpp
    src/private/ImGuiLayer.cpp
    src/private/Shader.cpp
    src/private/Buffer.cpp
    src/private/Renderer.cpp
    src/private/RenderCommandQueue
    src/private/Renderer2D.cpp
    src/private/VertexArray.cpp
    src/private/RenderCommand.cpp
    src/private/RendererAPI.cpp
    src/private/Camera.cpp
    src/private/Texture.cpp
    src/private/OrthographicCameraController.cpp
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

# Farscape engine if c++17
target_compile_features(Farscape PRIVATE cxx_std_17)

target_compile_definitions(Farscape PUBLIC "_CRT_SECURE_NO_WARNINGS")
# TODO: REMOVE THIS OR PUT IN DEBUG
target_compile_definitions(Farscape PUBLIC "FS_ENABLE_ASSERTS")


target_include_directories(Farscape 
    PUBLIC src/pch
    PUBLIC src/include
    PUBLIC ${FARSCAPE_BINARY_DIR}/generated
    PUBLIC src/platform
    PUBLIC src/Farscape
)

add_precompiled_header(Farscape fspch.h SOURCE_CXX src/pch/fspch.cpp FORCEINCLUDE)

target_link_libraries(Farscape
    PUBLIC spdlog::spdlog
    PUBLIC Farscape::imgui_gl3glfw
    PUBLIC glfw
    PUBLIC Farscape::glad
    PUBLIC glm::glm
    PUBLIC Farscape::stb
)

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