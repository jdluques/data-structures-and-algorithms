add_executable(singly_tests lists/singly_tests.cpp)
target_link_libraries(singly_tests PRIVATE ds_lists Catch2::Catch2WithMain)
add_test(NAME singly_tests COMMAND singly_tests)

add_executable(doubly_tests lists/doubly_tests.cpp)
target_link_libraries(doubly_tests PRIVATE ds_lists Catch2::Catch2WithMain)
add_test(NAME doubly_tests COMMAND doubly_tests)

add_executable(stack_tests stack_tests.cpp)
target_link_libraries(stack_tests PRIVATE ds_stack Catch2::Catch2WithMain)
add_test(NAME stack_tests COMMAND stack_tests)
