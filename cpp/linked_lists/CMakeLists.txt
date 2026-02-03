add_library(linked_lists INTERFACE)

target_include_directories(linked_lists INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/singly)

add_subdirectory(singly/tests)
