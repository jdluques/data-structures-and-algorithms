cmake_minimum_required(VERSION 3.16)
project(DataStructuresAlgorithms LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -----------------------------
# Header-only library target
# -----------------------------
add_library(ds INTERFACE)

target_include_directories(ds INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# -----------------------------
# Submodules
# -----------------------------
add_subdirectory(include)

# -----------------------------
# Fetch Catch2 for tests
# -----------------------------
include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.12.0
)

FetchContent_MakeAvailable(Catch2)

enable_testing()

# -----------------------------
# Add tests directory
# -----------------------------
add_subdirectory(tests)
