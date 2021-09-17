cmake_minimum_required(VERSION 3.14)
project(TDOR VERSION 0.1.0)

include(FetchContent)
set(FETCHCONTENT_QUIET NO)

include(${CMAKE_SOURCE_DIR}/cmake/EnsureRayLib.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/EnsureLua.cmake)
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(stech)
add_subdirectory(sedit)