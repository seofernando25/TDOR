cmake_minimum_required(VERSION 3.14)
project(Stech VERSION 0.1.0)

include(FetchContent)
set(FETCHCONTENT_QUIET NO)

include(${CMAKE_SOURCE_DIR}/cmake/EnsureRayLib.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/EnsureLua.cmake)

file(GLOB_RECURSE Stech-RUNTIME_FILES Runtime/**)

# Add files to library
add_library(Stech ${Stech-RUNTIME_FILES})
target_include_directories(
        Stech
        PUBLIC
        Runtime
)

target_link_libraries(Stech raylib ${LUA_LIBRARIES})

# Compile the editor
file(GLOB_RECURSE Stech-EDITOR_FILES Editor/**)

add_executable(StechEditor ${Stech-EDITOR_FILES})
target_include_directories(StechEditor
        PUBLIC
        Editor
        )

target_link_libraries(StechEditor Stech ${RAYLIB_LIBRARIES} ${LUA_LIBRARIES})