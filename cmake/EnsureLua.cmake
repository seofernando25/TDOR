cmake_minimum_required(VERSION 3.14)
include(FindLua)
find_package(Lua QUIET)

if (NOT LUA_FOUND)
    FetchContent_Declare(
            lua
            GIT_REPOSITORY https://github.com/marovira/lua
    )
    FetchContent_MakeAvailable(lua)
endif ()

include_directories(${LUA_INCLUDE_DIR})
