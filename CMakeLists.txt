cmake_minimum_required(VERSION 3.10)
project(TestSDL3 CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(test_sdl test_sdl.cpp)

# импортируем статическую SDL3
add_library(SDL3 STATIC IMPORTED)
set_target_properties(SDL3 PROPERTIES
    IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/lib/libSDL3.a"
)
target_include_directories(SDL3 INTERFACE
    ${CMAKE_SOURCE_DIR}/include   # путь к папке, где лежит SDL3/SDL.h
)

target_link_libraries(test_sdl PRIVATE SDL3)
