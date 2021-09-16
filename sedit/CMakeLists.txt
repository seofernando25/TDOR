include_directories(include)

# Get all files inside include and src directories
file(GLOB_RECURSE sedit_SRC_FILES src/*.c)
file(GLOB_RECURSE sedit_INCLUDE_FILES include/*.h)

# Add files to library
add_executable(sedit ${sedit_SRC_FILES} ${sedit_INCLUDE_FILES})
target_include_directories(sedit
        PUBLIC
        include
        PRIVATE
        src
        )

target_link_libraries(sedit stech ${RAYLIB_LIBRARIES} ${LUA_LIBRARIES})
