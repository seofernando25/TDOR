cmake_minimum_required(VERSION 3.11)
include(FindLua)
find_package(Lua REQUIRED)
include_directories(${PROJECT_NAME} ${LUA_INCLUDE_DIR})
