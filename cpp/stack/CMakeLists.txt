add_library(linked_lists INTERFACE)

target_include_directories(linked_lists INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(tests)