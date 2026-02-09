add_library(asm_singly_list
    singly/node.s
)

target_link_libraries(asm_singly_list
    PUBLIC project_includes
)

