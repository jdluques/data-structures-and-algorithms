add_subdirectory(linked_lists)

add_library(stack
    stack.c
)

target_link_libraries(stack
    PUBLIC project_includes
)
