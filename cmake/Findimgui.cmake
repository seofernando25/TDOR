
find_package(SDL2 CONFIG REQUIRED)
FetchContent_Declare(
        imgui
        URL "https://github.com/ocornut/imgui/archive/master.zip"
)

FetchContent_GetProperties(imgui)
if (NOT imgui_POPULATED)
    FetchContent_Populate(imgui)
endif ()

add_library(imgui)

target_link_libraries(imgui SDL2)

target_sources(
        imgui
        PRIVATE
        ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl.h
)

target_include_directories(imgui
        PUBLIC
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}


        )