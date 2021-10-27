file(GLOB_RECURSE SRENDERER_SOURCE_FILES **.cpp **.h)
add_library(SRenderer ${SRENDERER_SOURCE_FILES})
target_link_libraries(SRenderer  ${SDL2_LIBRARY} glad SGL)
target_include_directories(SRenderer PUBLIC ./)