# Linked Lists module
add_library(ds_lists INTERFACE)
target_include_directories(ds_lists INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/lists
)
target_link_libraries(ds_lists INTERFACE ds)

# Stack module
add_library(ds_stack INTERFACE)
target_include_directories(ds_stack INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(ds_stack INTERFACE ds)
