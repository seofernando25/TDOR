add_executable(sedit main.c)
target_include_directories(sedit PRIVATE ${RAYLIB_INCLUDE_DIRS} ${LUA_INCLUDE_DIR})
target_link_libraries(sedit PRIVATE stech ${RAYLIB_LIBRARIES} ${LUA_LIBRARIES})