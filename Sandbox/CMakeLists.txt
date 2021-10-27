file(GLOB_RECURSE SANDBOX_SOURCE_FILES *.cpp *.h)
add_executable(Sandbox ${SANDBOX_SOURCE_FILES})
target_link_libraries(Sandbox  ${SDL2_LIBRARY} glad SGL SSDL SAppSys)