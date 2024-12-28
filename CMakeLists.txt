cmake_minimum_required(VERSION 3.28)
project(GameBoy C)

set(CMAKE_C_STANDARD 11)

file(GLOB SOURCES
        src/*.c
        src/cpu/*.c
        src/mmu/*.c
        src/ppu/*.c
        src/debug/*.c
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
add_executable(GameBoy ${SOURCES} ${HEADERS} lib/libraylib.a
        src/ppu/ppu.h
        src/ppu/ppu.c
        src/ppu/fetcher.h
        src/ppu/fifo.h
        src/ppu/raylib.h)

target_include_directories(
        GameBoy PRIVATE
        src
        src/cpu
        src/mmu
        src/ppu
        src/debug
)

add_library(raylib STATIC IMPORTED)
set_target_properties(raylib PROPERTIES IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/lib/libraylib.a")
target_link_libraries(GameBoy PRIVATE
        raylib
        "-framework IOKit"
        "-framework Cocoa"
        "-framework OpenGL"
)