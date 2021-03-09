cmake_minimum_required(VERSION 3.18)

add_library(entt INTERFACE )

target_include_directories(entt 
    INTERFACE include/
)

add_library(Farscape::entt ALIAS entt)
