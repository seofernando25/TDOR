cmake_minimum_required(VERSION 3.14)
find_package(raylib CONFIG QUIET)

if (NOT raylib_FOUND)
    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/master.tar.gz
    )

    FetchContent_MakeAvailable(raylib)
endif()