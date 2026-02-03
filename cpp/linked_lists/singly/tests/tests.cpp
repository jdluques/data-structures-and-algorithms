#include <catch2/catch_test_macros.hpp>
#include <stdexcept>
#include <string>

#include "../list.hpp"

TEST_CASE("Default construction", "[constructor]") {
    SinglyLinkedList<int> list;

    REQUIRE(list.size() == 0);
    REQUIRE(list.empty());
    REQUIRE(list.begin() == list.end());
}

TEST_CASE("push_front", "[modifiers]") {
    SinglyLinkedList<int> list;

    list.push_front(1);
    REQUIRE(list.size() == 1);
    REQUIRE(list.front() == 1);
    REQUIRE(list.back() == 1);

    list.push_front(2);
    REQUIRE(list.size() == 2);
    REQUIRE(list.front() == 2);
    REQUIRE(list.back() == 1);
}

TEST_CASE("push_back", "[modifiers]") {
    SinglyLinkedList<int> list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    REQUIRE(list.size() == 3);
    REQUIRE(list.front() == 1);
    REQUIRE(list.back() == 3);
}

TEST_CASE("pop_front", "[modifiers]") {
    SinglyLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);

    list.pop_front();
    REQUIRE(list.size() == 1);
    REQUIRE(list.front() == 2);

    list.pop_front();
    REQUIRE(list.empty());

    REQUIRE_THROWS_AS(list.pop_front(), std::out_of_range);
}

TEST_CASE("pop_back", "[modifiers]") {
    SinglyLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.pop_back();
    REQUIRE(list.size() == 2);
    REQUIRE(list.back() == 2);

    list.pop_back();
    list.pop_back();
    REQUIRE(list.empty());

    REQUIRE_THROWS_AS(list.pop_back(), std::out_of_range);
}

TEST_CASE("insert at positions", "[modifiers]") {
    SinglyLinkedList<int> list;
    list.push_back(1);
    list.push_back(3);

    list.insert(2, 1);
    REQUIRE(list.size() == 3);
    REQUIRE(list[0] == 1);
    REQUIRE(list[1] == 2);
    REQUIRE(list[2] == 3);

    REQUIRE_THROWS_AS(list.insert(4, 10), std::out_of_range);
}

TEST_CASE("erase at positions", "[modifiers]") {
    SinglyLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.erase(1);
    REQUIRE(list.size() == 2);
    REQUIRE(list[0] == 1);
    REQUIRE(list[1] == 3);

    list.erase(0);
    REQUIRE(list.front() == 3);

    REQUIRE_THROWS_AS(list.erase(5), std::out_of_range);
}

TEST_CASE("element access: front, back, at, operator[]", "[access]") {
    SinglyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);

    REQUIRE(list.front() == 10);
    REQUIRE(list.back() == 20);
    REQUIRE(list.at(1) == 20);
    REQUIRE(list[0] == 10);

    REQUIRE_THROWS_AS(list.at(2), std::out_of_range);
    REQUIRE_THROWS_AS(list[3], std::out_of_range);
}

TEST_CASE("find", "[search]") {
    SinglyLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    auto* node = list.find(2);
    REQUIRE(node != nullptr);
    REQUIRE(node->value == 2);

    REQUIRE(list.find(42) == nullptr);
}

TEST_CASE("iterators traversal", "[iterators]") {
    SinglyLinkedList<int> list;
    for (int i = 1; i <= 5; ++i) list.push_back(i);

    int expected = 1;
    for (auto it = list.begin(); it != list.end(); ++it) {
        REQUIRE(*it == expected++);
    }
}

TEST_CASE("const_iterators traversal", "[iterators][const]") {
    SinglyLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);

    const auto& clist = list;

    int sum = 0;
    for (auto it = clist.cbegin(); it != clist.cend(); ++it) {
        sum += *it;
    }

    REQUIRE(sum == 3);
}

TEST_CASE("copy constructor creates deep copy", "[copy]") {
    SinglyLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);

    SinglyLinkedList<int> copy(list);
    copy.push_back(3);

    REQUIRE(list.size() == 2);
    REQUIRE(copy.size() == 3);
}

TEST_CASE("copy assignment creates deep copy", "[copy]") {
    SinglyLinkedList<int> a;
    a.push_back(1);
    a.push_back(2);

    SinglyLinkedList<int> b;
    b = a;
    b.push_back(3);

    REQUIRE(a.size() == 2);
    REQUIRE(b.size() == 3);
}

TEST_CASE("move constructor", "[move]") {
    SinglyLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);

    SinglyLinkedList<int> moved(std::move(list));

    REQUIRE(moved.size() == 2);
    REQUIRE(list.empty());
}

TEST_CASE("move assignment", "[move]") {
    SinglyLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);

    SinglyLinkedList<int> other;
    other = std::move(list);

    REQUIRE(other.size() == 2);
    REQUIRE(list.empty());
}

TEST_CASE("clear removes all elements", "[modifiers]") {
    SinglyLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);

    list.clear();
    REQUIRE(list.empty());
    REQUIRE(list.size() == 0);
}

TEST_CASE("works with non-trivial types", "[templates]") {
    SinglyLinkedList<std::string> list;
    list.push_back("hello");
    list.push_back("world");

    REQUIRE(list.front() == "hello");
    REQUIRE(list.back() == "world");
}

