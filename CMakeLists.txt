cmake_minimum_required(VERSION 3.15)
project(TDOR VERSION 0.0.0 LANGUAGES C)

# Dependencies
include(${CMAKE_SOURCE_DIR}/cmake/EnsureRayLib.cmake)

include(FindLua)
find_package(Lua REQUIRED)
include_directories(${PROJECT_NAME}  ${LUA_INCLUDE_DIR})

add_subdirectory(stech)
add_subdirectory(editor)