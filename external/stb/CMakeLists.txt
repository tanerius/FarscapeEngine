add_library(stb INTERFACE)

target_include_directories(stb 

    INTERFACE .
)

add_library(Farscape::stb ALIAS stb)