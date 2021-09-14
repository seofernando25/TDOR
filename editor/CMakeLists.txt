add_executable(sedit main.c)

find_package(raylib CONFIG REQUIRED)
target_include_directories(sedit PRIVATE ${RAYLIB_INCLUDE_DIRS})
target_link_libraries(sedit PRIVATE stech ${RAYLIB_LIBRARIES})