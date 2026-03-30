# Heaps module
add_library(ds_heaps INTERFACE)
target_include_directories(ds_heaps INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/heaps
)
target_link_libraries(ds_heaps INTERFACE ds)
