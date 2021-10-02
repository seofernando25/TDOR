cmake_minimum_required(VERSION 3.14)
find_package(glm QUIET)

if (NOT glm_FOUND)
    FetchContent_Declare(
            glm
            URL https://github.com/g-truc/glm/archive/master.tar.gz
    )
    FetchContent_MakeAvailable(glm)
endif ()