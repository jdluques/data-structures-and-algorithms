#pragma once

#include <vector>

template <typename T>
class Stack {
private:
    std::vector<T> data_;
public:
    Stack() = default;
    Stack(const Stack& other) = default;
    Stack(Stack&& other) noexcept = default;

    ~Stack() = default;

    Stack& operator=(Stack& other) = default;
    Stack& operator=(Stack&& other) noexcept = default;

    std::size_t size() const noexcept;
    bool empty() const noexcept;

    const T& top() const;
    T& top();

    void push(const T& element);
    void push(T&& element);

    template <class... Args>
    void emplace(Args&&... args);

    T pop();
    void clear() noexcept;

    bool operator==(const Stack& other) const;
    bool operator!=(const Stack& other) const;

    void swap(Stack& other) noexcept;
};

template <typename T>
void swap(Stack<T>& a, Stack<T>& b) noexcept;
