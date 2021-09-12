include_directories(${TDOR_SOURCE_DIR}/TDOR/inc)
# I assume you want to use LibProject as a library in MainProject.
include_directories(${TDOR_SOURCE_DIR}/LibProject/inc)
link_directories(${TDOR_SOURCE_DIR}/LibProject/src)
add_executable(TDOR main.c)
target_link_libraries(TDOR raylib)