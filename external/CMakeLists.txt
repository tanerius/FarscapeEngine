cmake_minimum_required(VERSION 3.18)

# Before adding externals make sure we grab the latest from github
# 1. Download all the submodules
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

# 2. Check all submodules
### spdlog
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/External/spdlog/CMakeLists.txt")
    message(FATAL_ERROR "Submodule spdlog not downloaded")
else()
	add_subdirectory(spdlog)
endif()

### glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/External/glfw/CMakeLists.txt")
    message(FATAL_ERROR "Submodule glfw not downloaded")
else()
	add_subdirectory(glfw)
endif()

### glad
add_subdirectory(glad)

### glm
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/External/glm/CMakeLists.txt")
    message(FATAL_ERROR "Submodule glm not downloaded")
else()
	add_subdirectory(glm)
endif()

### Farscape::stb
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/External/stb/CMakeLists.txt")
    message(FATAL_ERROR "Submodule stb not downloaded")
else()
	add_subdirectory(stb)
endif()

### Assimp
add_subdirectory(assimp)

### Mono
add_subdirectory(mono)

### entt
add_subdirectory(entt)

### FastNoiseLite
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/External/FastNoiseLite/CMakeLists.txt")
    message(FATAL_ERROR "Submodule FastNoiseLite not downloaded")
else()
	add_subdirectory(FastNoiseLite)
endif()

### GoogleTest
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/External/googletest/CMakeLists.txt")
    message(FATAL_ERROR "Submodule googletest not downloaded")
else()
	add_subdirectory(googletest)
endif()