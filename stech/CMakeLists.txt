
include_directories(include)

# Get all files inside include and src directories
file(GLOB_RECURSE stech_SRC_DIR src/*.c)
file(GLOB_RECURSE stech_INCLUDE_DIR include/*.h)

# Add files to library
add_library(stech ${stech_SRC_DIR} ${stech_INCLUDE_DIR})
target_include_directories(stech
    PUBLIC
        include
    PRIVATE
        src
 )