add_library(asm_singly_list
    singly/node.s
    singly/list.s
    singly/size.s
)

target_link_libraries(asm_singly_list
    PUBLIC project_includes
)

