add_library(linked_lists_singly
    singly.c
)

target_link_libraries(linked_lists_singly
    PUBLIC project_includes
)


add_library(linked_lists_doubly
    doubly.c
)

target_link_libraries(linked_lists_doubly
    PUBLIC project_includes
)

