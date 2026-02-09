cmake_minimum_required(VERSION 3.16)
project(asm_dsa LANGUAGES C ASM)

enable_language(ASM)

add_library(project_includes INTERFACE)
target_include_directories(project_includes INTERFACE
    ${PROJECT_SOURCE_DIR}/include
)

add_subdirectory(src)
