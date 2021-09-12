cmake_minimum_required(VERSION 3.15)
project(TDOR VERSION 0.0.0)

#include(CTest)
#enable_testing()

# Lua
include(FindLua)
find_package(Lua REQUIRED)
include_directories(${PROJECT_NAME}  ${LUA_INCLUDE_DIR})

# Raylib
find_package(raylib CONFIG QUIET)

if (NOT raylib_FOUND)
  include(FetchContent)

  FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/master.tar.gz
  )

  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)

    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples

    # build raylib
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()


add_subdirectory(TDOR)