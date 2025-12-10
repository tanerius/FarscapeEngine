cmake_minimum_required(VERSION 3.20)
project(Farscape VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Vulkan (required)
find_package(Vulkan REQUIRED)

# Try to find GLFW
find_package(glfw3 QUIET)
if(NOT glfw3_FOUND)
    message(STATUS "GLFW not found via find_package, looking for manual installation...")
    
    # Platform-specific search paths
    if(WIN32)
        set(GLFW_SEARCH_PATHS
            ${CMAKE_SOURCE_DIR}/external/windows/glfw/include
            ${CMAKE_SOURCE_DIR}/external/glfw/include
            $ENV{GLFW_DIR}/include
            "C:/Program Files/GLFW/include"
        )
        # Visual Studio version-specific lib folders
        set(GLFW_LIB_SEARCH_PATHS
            ${CMAKE_SOURCE_DIR}/external/windows/glfw/lib-vc2022
            ${CMAKE_SOURCE_DIR}/external/windows/glfw/lib-vc2019
            ${CMAKE_SOURCE_DIR}/external/windows/glfw/lib-vc2017
            ${CMAKE_SOURCE_DIR}/external/windows/glfw/lib-static-ucrt
            ${CMAKE_SOURCE_DIR}/external/windows/glfw/lib
            ${CMAKE_SOURCE_DIR}/external/glfw/lib
            $ENV{GLFW_DIR}/lib
            "C:/Program Files/GLFW/lib"
        )
    elseif(UNIX AND NOT APPLE)
        set(GLFW_SEARCH_PATHS
            ${CMAKE_SOURCE_DIR}/external/linux/glfw/include
            ${CMAKE_SOURCE_DIR}/external/glfw/include
            $ENV{GLFW_DIR}/include
            /usr/local/include
            /usr/include
        )
        set(GLFW_LIB_SEARCH_PATHS
            ${CMAKE_SOURCE_DIR}/external/linux/glfw/lib
            ${CMAKE_SOURCE_DIR}/external/glfw/lib
            $ENV{GLFW_DIR}/lib
            /usr/local/lib
            /usr/lib
            /usr/lib/x86_64-linux-gnu
        )
    else() # macOS
        set(GLFW_SEARCH_PATHS
            ${CMAKE_SOURCE_DIR}/external/macos/glfw/include
            ${CMAKE_SOURCE_DIR}/external/glfw/include
            $ENV{GLFW_DIR}/include
            /usr/local/include
            /opt/homebrew/include
        )
        set(GLFW_LIB_SEARCH_PATHS
            ${CMAKE_SOURCE_DIR}/external/macos/glfw/lib
            ${CMAKE_SOURCE_DIR}/external/glfw/lib
            $ENV{GLFW_DIR}/lib
            /usr/local/lib
            /opt/homebrew/lib
        )
    endif()
    
    find_path(GLFW_INCLUDE_DIR GLFW/glfw3.h PATHS ${GLFW_SEARCH_PATHS})
    find_library(GLFW_LIBRARY 
        NAMES glfw3 glfw
        PATHS ${GLFW_LIB_SEARCH_PATHS}
    )
    
    if(GLFW_INCLUDE_DIR AND GLFW_LIBRARY)
        add_library(glfw UNKNOWN IMPORTED)
        set_target_properties(glfw PROPERTIES
            IMPORTED_LOCATION "${GLFW_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${GLFW_INCLUDE_DIR}"
        )
        # Linux-specific dependencies
        if(UNIX AND NOT APPLE)
            target_link_libraries(glfw INTERFACE pthread dl)
            find_package(X11 REQUIRED)
            target_link_libraries(glfw INTERFACE ${X11_LIBRARIES})
        endif()
        message(STATUS "Found GLFW manually: ${GLFW_LIBRARY}")
    else()
        if(UNIX AND NOT APPLE)
            message(FATAL_ERROR "GLFW not found. Install with: sudo apt-get install libglfw3-dev")
        else()
            message(FATAL_ERROR "GLFW not found. Please install or set GLFW_DIR environment variable.")
        endif()
    endif()
endif()

# Try to find GLM (header-only library)
find_package(glm QUIET)
if(NOT glm_FOUND)
    message(STATUS "GLM not found via find_package, looking for headers...")
    
    # GLM is header-only, so platform doesn't matter, but keep structure consistent
    set(GLM_SEARCH_PATHS
        ${CMAKE_SOURCE_DIR}/external/glm
        $ENV{GLM_DIR}
    )
    
    if(WIN32)
        list(APPEND GLM_SEARCH_PATHS "C:/Program Files/glm")
    else()
        list(APPEND GLM_SEARCH_PATHS /usr/local/include /usr/include)
    endif()
    
    find_path(GLM_INCLUDE_DIR glm/glm.hpp PATHS ${GLM_SEARCH_PATHS})
    
    if(GLM_INCLUDE_DIR)
        add_library(glm INTERFACE)
        target_include_directories(glm INTERFACE ${GLM_INCLUDE_DIR})
        add_library(glm::glm ALIAS glm)
        message(STATUS "Found GLM headers: ${GLM_INCLUDE_DIR}")
    else()
        if(UNIX AND NOT APPLE)
            message(FATAL_ERROR "GLM not found. Install with: sudo apt-get install libglm-dev")
        else()
            message(FATAL_ERROR "GLM not found. Please install or set GLM_DIR environment variable.")
        endif()
    endif()
endif()

# Source files
set(SOURCES
    src/main.cpp
    src/VulkanApp.cpp
    src/CubeGeometry.cpp
    src/RenderObject.cpp
    src/Scene.cpp
    src/Renderer.cpp
)

# Header files
set(HEADERS
    include/VulkanApp.h
    include/CubeGeometry.h
    include/RenderObject.h
    include/Scene.h
    include/Renderer.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${Vulkan_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    Vulkan::Vulkan
    glfw
    glm::glm
)

# Platform-specific linking
if(UNIX AND NOT APPLE)
    # Linux-specific libraries
    target_link_libraries(${PROJECT_NAME} PRIVATE pthread dl)
    find_package(X11 REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${X11_LIBRARIES})
elseif(WIN32)
    # Windows doesn't need additional system libraries for Vulkan/GLFW
endif()

# Compiler-specific options
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Copy shaders to build directory
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/shaders)

# Compile shaders
find_program(GLSLC glslc HINTS ${Vulkan_INCLUDE_DIRS}/../Bin)

if(GLSLC)
    message(STATUS "Found glslc: ${GLSLC}")
    
    # Compile vertex shader
    add_custom_command(
        OUTPUT ${CMAKE_BINARY_DIR}/shaders/vert.spv
        COMMAND ${GLSLC} ${CMAKE_SOURCE_DIR}/shaders/shader.vert -o ${CMAKE_BINARY_DIR}/shaders/vert.spv
        DEPENDS ${CMAKE_SOURCE_DIR}/shaders/shader.vert
        COMMENT "Compiling vertex shader"
    )
    
    # Compile fragment shader
    add_custom_command(
        OUTPUT ${CMAKE_BINARY_DIR}/shaders/frag.spv
        COMMAND ${GLSLC} ${CMAKE_SOURCE_DIR}/shaders/shader.frag -o ${CMAKE_BINARY_DIR}/shaders/frag.spv
        DEPENDS ${CMAKE_SOURCE_DIR}/shaders/shader.frag
        COMMENT "Compiling fragment shader"
    )
    
    # Add custom target for shaders
    add_custom_target(Shaders ALL
        DEPENDS 
            ${CMAKE_BINARY_DIR}/shaders/vert.spv
            ${CMAKE_BINARY_DIR}/shaders/frag.spv
    )
    
    add_dependencies(${PROJECT_NAME} Shaders)
else()
    message(WARNING "glslc not found. Shaders will not be compiled automatically.")
endif()
