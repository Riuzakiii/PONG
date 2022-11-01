cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

file(GLOB_RECURSE SDLYogurtFiles LIST_DIRECTORIES false *.cpp *.h)

add_library(SDLYogurt STATIC ${SDLYogurtFiles})

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

target_compile_options(
SDLYogurt
PUBLIC $<$<CXX_COMPILER_ID:MSVC>:
        /W4
        /WX>
        $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Debug>>:
        /MTd
        /Od>
        $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Release>>:
        /MT
        /O2>
        $<$<CXX_COMPILER_ID:MSVC>:
        /W4
        /WX>)

target_compile_options(
SDLYogurt
PUBLIC $<$<CXX_COMPILER_ID:Clang,GNU,AppleClang>:
        -pedantic -Wall -Wextra -Wconversion
        >
        $<$<AND:$<CXX_COMPILER_ID:Clang,GNU,AppleClang>,$<CONFIG:Debug>>:
        -O0>
        $<$<AND:$<CXX_COMPILER_ID:Clang,GNU,AppleClang>,$<CONFIG:Release>>:
        -O2 -Werror>
)

set_target_properties(SDLYogurt PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")

target_include_directories(SDLYogurt PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../SDL_ttf)
target_include_directories(SDLYogurt PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src/game ${CMAKE_CURRENT_LIST_DIR}/src/core/rendering ${CMAKE_CURRENT_LIST_DIR}/src/core/time ${CMAKE_CURRENT_LIST_DIR}/src/core/devices ${CMAKE_CURRENT_LIST_DIR}/src/gui/GUIElements ${CMAKE_CURRENT_LIST_DIR}/src/gui/Windows  ${CMAKE_CURRENT_LIST_DIR}/src/core )
target_link_libraries(SDLYogurt PRIVATE SDL2::Core SDL2::TTF SDL2::Image)
