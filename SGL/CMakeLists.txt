file(GLOB_RECURSE SGL_SOURCE_FILES *.cpp *.h)
add_library(SGL ${SGL_SOURCE_FILES})
target_link_libraries(SGL  ${SDL2_LIBRARY} glad glm::glm)
target_include_directories(SGL PUBLIC ./)