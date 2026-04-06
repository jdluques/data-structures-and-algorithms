# Linked Lists
add_library(lists_singly lists/singly.c)
target_link_libraries(lists_singly PUBLIC project_includes)

add_library(lists_doubly lists/doubly.c)
target_link_libraries(lists_doubly PUBLIC project_includes)

# Stack
add_library(stack stack.c)
target_link_libraries(stack PUBLIC project_includes)
