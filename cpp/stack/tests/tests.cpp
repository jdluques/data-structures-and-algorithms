#include <catch2/catch_test_macros.hpp>
#include <stdexcept>
#include <string>
#include <utility>

#include "../stack.hpp"

TEST_CASE("Default construction", "[constructor]") {
    Stack<int> stack;

    REQUIRE(stack.size() == 0);
    REQUIRE(stack.empty());
}

TEST_CASE("push(const T&) and top", "[modifiers]") {
    Stack<int> stack;

    stack.push(1);
    REQUIRE(stack.size() == 1);
    REQUIRE(stack.top() == 1);

    stack.push(2);
    REQUIRE(stack.size() == 2);
    REQUIRE(stack.top() == 2);
}

TEST_CASE("push(T&&) moves value", "[modifiers][move]") {
    Stack<std::string> stack;

    std::string s = "hello";
    stack.push(std::move(s));

    REQUIRE(stack.size() == 1);
    REQUIRE(stack.top() == "hello");
}

TEST_CASE("emplace constructs in place", "[modifiers][emplace]") {
    Stack<std::string> stack;

    stack.emplace(5, 'a'); // "aaaaa"
    REQUIRE(stack.size() == 1);
    REQUIRE(stack.top() == "aaaaa");
}

TEST_CASE("pop removes and returns top element", "[modifiers]") {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);

    int value = stack.pop();
    REQUIRE(value == 2);
    REQUIRE(stack.size() == 1);
    REQUIRE(stack.top() == 1);
}

TEST_CASE("pop on empty stack throws", "[modifiers][exceptions]") {
    Stack<int> stack;
    REQUIRE_THROWS_AS(stack.pop(), std::out_of_range);
}

TEST_CASE("top on empty stack throws", "[access][exceptions]") {
    Stack<int> stack;
    REQUIRE_THROWS_AS(stack.top(), std::out_of_range);
}

TEST_CASE("const top access", "[access][const]") {
    Stack<int> stack;
    stack.push(42);

    const Stack<int>& cstack = stack;
    REQUIRE(cstack.top() == 42);
}

TEST_CASE("clear removes all elements", "[modifiers]") {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);

    stack.clear();
    REQUIRE(stack.empty());
    REQUIRE(stack.size() == 0);
}

TEST_CASE("operator== and operator!=", "[operators]") {
    Stack<int> a;
    Stack<int> b;

    a.push(1);
    a.push(2);

    b.push(1);
    b.push(2);

    REQUIRE(a == b);
    REQUIRE_FALSE(a != b);

    b.push(3);
    REQUIRE(a != b);
}

TEST_CASE("copy constructor creates deep copy", "[copy]") {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);

    Stack<int> copy(stack);
    copy.push(3);

    REQUIRE(stack.size() == 2);
    REQUIRE(copy.size() == 3);
    REQUIRE(stack.top() == 2);
    REQUIRE(copy.top() == 3);
}

TEST_CASE("copy assignment creates deep copy", "[copy]") {
    Stack<int> a;
    a.push(1);
    a.push(2);

    Stack<int> b;
    b = a;
    b.push(3);

    REQUIRE(a.size() == 2);
    REQUIRE(b.size() == 3);
}

TEST_CASE("move constructor transfers ownership", "[move]") {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);

    Stack<int> moved(std::move(stack));

    REQUIRE(moved.size() == 2);
    REQUIRE(moved.top() == 2);
    REQUIRE(stack.empty());
}

TEST_CASE("move assignment transfers ownership", "[move]") {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);

    Stack<int> other;
    other = std::move(stack);

    REQUIRE(other.size() == 2);
    REQUIRE(other.top() == 2);
    REQUIRE(stack.empty());
}

TEST_CASE("swap exchanges contents", "[swap]") {
    Stack<int> a;
    Stack<int> b;

    a.push(1);
    a.push(2);
    b.push(9);

    a.swap(b);

    REQUIRE(a.size() == 1);
    REQUIRE(a.top() == 9);

    REQUIRE(b.size() == 2);
    REQUIRE(b.top() == 2);
}

TEST_CASE("free swap works (ADL)", "[swap]") {
    Stack<int> a;
    Stack<int> b;

    a.push(1);
    b.push(2);

    using std::swap;
    swap(a, b);

    REQUIRE(a.top() == 2);
    REQUIRE(b.top() == 1);
}

TEST_CASE("works with non-trivial types", "[templates]") {
    Stack<std::string> stack;

    stack.push("hello");
    stack.push("world");

    REQUIRE(stack.top() == "world");

    auto value = stack.pop();
    REQUIRE(value == "world");
    REQUIRE(stack.top() == "hello");
}

