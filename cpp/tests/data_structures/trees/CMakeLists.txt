add_executable(heap_tests heaps/heap_tests.cpp)
target_link_libraries(heap_tests PRIVATE ds_heaps Catch2::Catch2WithMain)
add_test(NAME heap_tests COMMAND heap_tests)
