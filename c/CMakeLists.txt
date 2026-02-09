cmake_minimum_required(VERSION 3.16)
project(data_structures C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(project_includes INTERFACE)
target_include_directories(project_includes INTERFACE
    ${PROJECT_SOURCE_DIR}/include
)

add_subdirectory(src/linked_lists)
