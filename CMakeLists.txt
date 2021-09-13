cmake_minimum_required(VERSION 3.15)
project(TDOR VERSION 0.0.0)

#include(CTest)
#enable_testing()

# Lua
#include(FindLua)
#find_package(Lua REQUIRED)
#include_directories(${PROJECT_NAME}  ${LUA_INCLUDE_DIR})


include(scripts/EnsureRayLib.cmake)

add_subdirectory(src)