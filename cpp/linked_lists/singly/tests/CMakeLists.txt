enable_testing()

add_executable(singly_lists_tests tests.cpp)

target_link_libraries(singly_lists_tests
    PRIVATE
        singly_list
        Catch2::Catch2WithMain
)

include(CTest)
include(Catch)

catch_discover_tests(singly_lists_tests)
