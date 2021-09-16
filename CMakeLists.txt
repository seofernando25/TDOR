cmake_minimum_required(VERSION 3.15)
project(TDOR VERSION 0.0.0 LANGUAGES C)

# Dependencies
# raylib
include(${CMAKE_SOURCE_DIR}/cmake/EnsureRayLib.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/EnsureLua.cmake)

add_subdirectory(stech)
add_subdirectory(sedit)