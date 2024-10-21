cmake_minimum_required(VERSION 3.28)
project(boy C)

set(CMAKE_C_STANDARD 11)

# Specify the include directories
include_directories(include)

# Gather all source files in the src directory
file(GLOB SOURCES "src/*.c")

# Check if any source files were found
if(NOT SOURCES)
    message(FATAL_ERROR "No source files found in the 'src' directory.")
endif()

# Add the raylib library as an imported static library
add_library(raylib STATIC IMPORTED)
set_target_properties(raylib PROPERTIES IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/lib/libraylib.a")

# Create the executable
add_executable(Game-boy ${SOURCES})

# Link the raylib library to the executable
target_link_libraries(Game-boy raylib)

# Optional: Enable clang-tidy
set(CMAKE_C_CLANG_TIDY "clang-tidy;-checks=*")
