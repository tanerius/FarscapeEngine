cmake_minimum_required(VERSION 3.12)

add_subdirectory(libs)

set(FS_PLATFORM_SPECIFIC_SRC_PATH "src/Farscape/platform")


if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    set(BUILD_SHARED_LIBS TRUE)
endif()

# Set the relevant platform dependant sources
if (WIN32)
    set(FS_SPECIFIC_SOURCES 
        "${FS_PLATFORM_SPECIFIC_SRC_PATH}/Windows/WindowsWindow.cpp"
        "${FS_PLATFORM_SPECIFIC_SRC_PATH}/Windows/WindowsWindow.h"
        "${FS_PLATFORM_SPECIFIC_SRC_PATH}/Windows/WindowsInput.cpp"
        "${FS_PLATFORM_SPECIFIC_SRC_PATH}/Windows/OpenGLBuffer.cpp"
        "${FS_PLATFORM_SPECIFIC_SRC_PATH}/Windows/OpenGLBuffer.h"
        "${FS_PLATFORM_SPECIFIC_SRC_PATH}/Windows/OpenGLVertexArray.h"
        "${FS_PLATFORM_SPECIFIC_SRC_PATH}/Windows/OpenGLVertexArray.cpp"
        "${FS_PLATFORM_SPECIFIC_SRC_PATH}/Windows/OpenGLRendererAPI.cpp"
        "${FS_PLATFORM_SPECIFIC_SRC_PATH}/Windows/OpenGLShader.h"
        "${FS_PLATFORM_SPECIFIC_SRC_PATH}/Windows/OpenGLShader.cpp"
        "${FS_PLATFORM_SPECIFIC_SRC_PATH}/Windows/OpenGLTexture.h"
        "${FS_PLATFORM_SPECIFIC_SRC_PATH}/Windows/OpenGLTexture.cpp"
        "${FS_PLATFORM_SPECIFIC_SRC_PATH}/Windows/OpenGLFramebuffer.h"
        "${FS_PLATFORM_SPECIFIC_SRC_PATH}/Windows/OpenGLFramebuffer.cpp"
        "${FS_PLATFORM_SPECIFIC_SRC_PATH}/Windows/OpenGLRenderPass.h"
        "${FS_PLATFORM_SPECIFIC_SRC_PATH}/Windows/OpenGLRenderPass.cpp"
        "${FS_PLATFORM_SPECIFIC_SRC_PATH}/Windows/OpenGLShaderUniform.h"
        "${FS_PLATFORM_SPECIFIC_SRC_PATH}/Windows/OpenGLShaderUniform.cpp"
    )
elseif (APPLE)
    set(FS_SPECIFIC_SOURCES 
        "${FS_PLATFORM_SPECIFIC_SRC_PATH}/Macos/AppleWindow.cpp"
        "${FS_PLATFORM_SPECIFIC_SRC_PATH}/Macos/AppleWindow.h"
    )
endif ()


set(FS_SOURCES 
    src/pch/fspch.h
    src/pch/fspch.cpp
    src/Farscape/Core/Application.cpp
    src/Farscape/Core/Log.cpp
    src/Farscape/Core/Core.cpp
    src/Farscape/Core/Layer.cpp
    src/Farscape/Core/Window.cpp
    src/Farscape/Renderer/Framebuffer.cpp
    ${FS_SPECIFIC_SOURCES}
    src/Farscape/Core/Layer.cpp
    src/Farscape/Core/LayerStack.cpp
    src/Farscape/ImGui/ImGuiLayer.cpp
    src/Farscape/Renderer/Shader.cpp
    src/Farscape/Renderer/Buffer.cpp
    src/Farscape/Renderer/Renderer.cpp
    src/Farscape/Renderer/RenderCommandQueue
    src/Farscape/Renderer/Renderer2D.cpp
    src/Farscape/Renderer/VertexArray.cpp
    src/Farscape/Renderer/RendererAPI.cpp
    src/Farscape/Renderer/Camera.cpp
    src/Farscape/Renderer/Texture.cpp
    src/Farscape/ImGui/ImGuizmo.cpp
    src/Farscape/Renderer/RenderPass.cpp
    src/Farscape/Renderer/Material.cpp
    src/Farscape/Renderer/Mesh.cpp
    src/Farscape/Core/Math/Mat4.cpp
    src/Farscape/Renderer/SceneRenderer.cpp
    src/Farscape/Scene/Entity.cpp
    src/Farscape/Scene/Scene.cpp
    src/Farscape/Core/Timestep.cpp
    src/Farscape/Editor/SceneHierarchyPanel.cpp
 )

 # OpenGL
find_package(OpenGL REQUIRED)

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

target_compile_definitions(Farscape 
    PUBLIC "_CRT_SECURE_NO_WARNINGS"
)
# TODO: REMOVE THIS OR PUT IN DEBUG
target_compile_definitions(Farscape PUBLIC "FS_DEBUG")


target_include_directories(Farscape 
    PUBLIC src/pch
    PUBLIC src/include
    PUBLIC src/Farscape
    PUBLIC ${FARSCAPE_BINARY_DIR}/generated
    PUBLIC src/platform
    PUBLIC ${OPENGL_INCLUDE_DIRS}
)

add_precompiled_header(Farscape fspch.h SOURCE_CXX src/pch/fspch.cpp FORCEINCLUDE)

target_link_libraries(Farscape
    PUBLIC spdlog::spdlog
    PUBLIC Farscape::imgui_gl3glfw
    PUBLIC glfw
    PUBLIC Farscape::glad
    PUBLIC glm::glm
    PUBLIC Farscape::stb
    PUBLIC Farscape::assimp
    ${OPENGL_LIBRARIES}
    PUBLIC ${FARSCAPE_ASSIMP_LIB}
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