file(GLOB_RECURSE SAPPSYS_SOURCE_FILES **.cpp **.h)
add_library(SAppSys ${SAPPSYS_SOURCE_FILES})
target_link_libraries(SAppSys  ${SDL2_LIBRARY} glad SGL)
target_include_directories(SAppSys PUBLIC ./)
target_precompile_headers(SAppSys PUBLIC "spch.h")