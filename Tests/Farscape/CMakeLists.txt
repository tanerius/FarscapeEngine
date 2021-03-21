cmake_minimum_required(VERSION 3.18)

project(FarscapeTests)

file(GLOB_RECURSE FS_TEST_SOURCES
            LIST_DIRECTORIES false 
            src/*
        )

add_executable(${PROJECT_NAME} ${FS_TEST_SOURCES})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_link_libraries(${PROJECT_NAME}
    PUBLIC Farscape::Farscape
    PRIVATE gtest
)
