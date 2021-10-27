cmake_minimum_required(VERSION 3.14)
project(TDOR VERSION 0.1.0)

include(FetchContent)
set(FETCHCONTENT_QUIET NO)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

include(${CMAKE_SOURCE_DIR}/cmake/EnsureGLM.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/EnsureLua.cmake)
find_package(SDL2 REQUIRED)
find_package(sdl2-image REQUIRED)
#find_package(imgui REQUIRED)


file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

#add_subdirectory(Stech)
add_subdirectory(SGL)
add_subdirectory(SRenderer)
add_subdirectory(SSDL)
add_subdirectory(SAppSys)

add_subdirectory(Sandbox)