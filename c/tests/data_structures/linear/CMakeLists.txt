add_executable(singly_tests lists/singly_tests.c)
target_link_libraries(singly_tests lists_singly)
add_test(NAME SinglyLinkedListTests COMMAND singly_tests)


add_executable(doubly_tests lists/doubly_tests.c)
target_link_libraries(doubly_tests lists_doubly)
add_test(NAME DoublyLinkedListTests COMMAND doubly_tests)
