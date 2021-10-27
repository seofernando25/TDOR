file(GLOB_RECURSE SSDL_SOURCE_FILES *.cpp *.h)
add_library(SSDL ${SSDL_SOURCE_FILES})
target_link_libraries(SSDL ${SDL2_LIBRARY} glad SAppSys)
target_include_directories(SSDL PUBLIC ./)