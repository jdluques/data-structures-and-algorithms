#include "data_structures/trees/heaps/heap.hpp"

#include <catch2/catch_test_macros.hpp>

#include <stdexcept>
#include <string>
#include <vector>
#include <functional>

TEST_CASE("Default construction", "[constructor]") {
    ds::Heap<int> heap;

    REQUIRE(heap.size() == 0);
    REQUIRE(heap.empty());
}

TEST_CASE("default comparator creates max-heap", "[constructor][comparator]") {
    ds::Heap<int> heap;

    heap.push(1);
    heap.push(3);
    heap.push(2);

    REQUIRE(heap.peek() == 3);
}

TEST_CASE("greater comparator creates max-heap", "[comparator]") {
    ds::Heap<int, std::greater<int>> heap;

    heap.push(1);
    heap.push(3);
    heap.push(2);

    REQUIRE(heap.pop() == 3);
    REQUIRE(heap.pop() == 2);
    REQUIRE(heap.pop() == 1);
}

TEST_CASE("less comparator creates min-heap", "[comparator]") {
    ds::Heap<int, std::less<int>> heap;

    heap.push(1);
    heap.push(3);
    heap.push(2);

    REQUIRE(heap.pop() == 1);
    REQUIRE(heap.pop() == 2);
    REQUIRE(heap.pop() == 3);
}

TEST_CASE("push and peek", "[modifiers]") {
    ds::Heap<int> heap;

    heap.push(10);
    REQUIRE(heap.peek() == 10);

    heap.push(20);
    REQUIRE(heap.peek() == 20);

    heap.push(5);
    REQUIRE(heap.peek() == 20);
}

TEST_CASE("pop removes and returns top element", "[modifiers]") {
    ds::Heap<int> heap;

    heap.push(1);
    heap.push(3);
    heap.push(2);

    int value = heap.pop();
    REQUIRE(value == 3);
    REQUIRE(heap.size() == 2);
    REQUIRE(heap.peek() == 2);
}

TEST_CASE("pop maintains heap property (max-heap)", "[modifiers]") {
    ds::Heap<int> heap;

    heap.push(5);
    heap.push(1);
    heap.push(4);
    heap.push(2);
    heap.push(3);

    REQUIRE(heap.pop() == 5);
    REQUIRE(heap.pop() == 4);
    REQUIRE(heap.pop() == 3);
    REQUIRE(heap.pop() == 2);
    REQUIRE(heap.pop() == 1);
}

TEST_CASE("pop maintains heap property (min-heap)", "[modifiers]") {
    ds::Heap<int, std::less<int>> heap;

    heap.push(5);
    heap.push(1);
    heap.push(4);
    heap.push(2);
    heap.push(3);

    REQUIRE(heap.pop() == 1);
    REQUIRE(heap.pop() == 2);
    REQUIRE(heap.pop() == 3);
    REQUIRE(heap.pop() == 4);
    REQUIRE(heap.pop() == 5);
}

TEST_CASE("pop on empty heap throws", "[modifiers][exceptions]") {
    ds::Heap<int> heap;

    REQUIRE_THROWS_AS(heap.pop(), std::out_of_range);
}

TEST_CASE("peek on empty heap throws", "[access][exceptions]") {
    ds::Heap<int> heap;

    REQUIRE_THROWS_AS(heap.peek(), std::out_of_range);
}

TEST_CASE("heapify constructor builds valid heap (max-heap)", "[constructor]") {
    std::vector<int> data = {5, 3, 4, 1, 2};

    ds::Heap<int> heap(data);

    REQUIRE(heap.size() == 5);
    REQUIRE(heap.peek() == 5);
}

TEST_CASE("heapify produces sorted order when popping (max-heap)", "[constructor]") {
    std::vector<int> data = {5, 3, 4, 1, 2};

    ds::Heap<int> heap(data);

    REQUIRE(heap.pop() == 5);
    REQUIRE(heap.pop() == 4);
    REQUIRE(heap.pop() == 3);
    REQUIRE(heap.pop() == 2);
    REQUIRE(heap.pop() == 1);
}

TEST_CASE("heapify works for min-heap", "[constructor]") {
    std::vector<int> data = {5, 3, 4, 1, 2};

    ds::Heap<int, std::less<int>> heap(data);

    REQUIRE(heap.peek() == 1);
}

TEST_CASE("clear removes all elements", "[modifiers]") {
    ds::Heap<int> heap;

    heap.push(1);
    heap.push(2);

    heap.clear();

    REQUIRE(heap.empty());
    REQUIRE(heap.size() == 0);
}

TEST_CASE("works with duplicate elements", "[modifiers]") {
    ds::Heap<int> heap;

    heap.push(2);
    heap.push(2);
    heap.push(1);

    REQUIRE(heap.pop() == 2);
    REQUIRE(heap.pop() == 2);
    REQUIRE(heap.pop() == 1);
}

TEST_CASE("works with strings", "[templates]") {
    ds::Heap<std::string> heap;

    heap.push("apple");
    heap.push("banana");
    heap.push("cherry");

    REQUIRE(heap.peek() == "cherry");

    auto value = heap.pop();
    REQUIRE(value == "cherry");
    REQUIRE(heap.peek() == "banana");
}

TEST_CASE("interleaved push and pop", "[modifiers]") {
    ds::Heap<int> heap;

    heap.push(3);
    heap.push(1);
    REQUIRE(heap.pop() == 3);

    heap.push(2);
    REQUIRE(heap.pop() == 2);
    REQUIRE(heap.pop() == 1);
}

TEST_CASE("single element push/pop", "[modifiers]") {
    ds::Heap<int> heap;

    heap.push(42);
    REQUIRE(heap.peek() == 42);

    REQUIRE(heap.pop() == 42);
    REQUIRE(heap.empty());
}

TEST_CASE("custom comparator works", "[comparator]") {
    struct AbsCompare {
        bool operator()(int a, int b) const {
            return std::abs(a) > std::abs(b);
        }
    };

    ds::Heap<int, AbsCompare> heap;

    heap.push(-10);
    heap.push(3);
    heap.push(-2);

    REQUIRE(heap.pop() == -10);
    REQUIRE(heap.pop() == 3);
    REQUIRE(heap.pop() == -2);
}
