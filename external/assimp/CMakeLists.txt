cmake_minimum_required(VERSION 3.12)

add_library(assimp SHARED IMPORTED )

set_target_properties(assimp PROPERTIES
  IMPORTED_LOCATION "win64/"
  IMPORTED_IMPLIB "win64/assimp.lib"
  INTERFACE_INCLUDE_DIRECTORIES include/
)

add_library(assimp::assimp ALIAS assimp)
