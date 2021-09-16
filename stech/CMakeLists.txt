# Get all files inside include and src directories
file(GLOB_RECURSE stech_SRC_FILES src/*.c)
file(GLOB_RECURSE stech_INCLUDE_FILES include/*.h)

# Add files to library
add_library(stech ${stech_SRC_FILES} ${stech_INCLUDE_FILES})
target_include_directories(stech
        PUBLIC
        include
        PRIVATE
        src
        )

target_link_libraries(stech raylib)