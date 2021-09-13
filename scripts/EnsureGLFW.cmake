cmake_minimum_required(VERSION 3.11)
find_package(glfw QUIET)

if (NOT glfw_FOUND)
    include(FetchContent)

    FetchContent_Declare(
            glfw
            GIT_REPOSITORY https://github.com/glfw/glfw
    )

    FetchContent_GetProperties(glfw)
    if (NOT glfw_POPULATED) # Have we downloaded glfw?
        set(FETCHCONTENT_QUIET NO)

        # Disable tests, examples, etc
        set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
        set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
        set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
        set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")

        FetchContent_Populate(glfw)


        # build glfw
        add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
    endif()
endif()
