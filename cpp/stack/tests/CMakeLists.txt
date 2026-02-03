enable_testing()

add_executable(stack_tests tests.cpp)

target_link_libraries(stack_tests
    PRIVATE
        stack
        Catch2::Catch2WithMain
)

include(CTest)
include(Catch)

catch_discover_tests(stack_tests)