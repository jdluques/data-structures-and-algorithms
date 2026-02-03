#include "stack.hpp"

#include <stdexcept>

// ### Capacity methods ###

template <typename T>
std::size_t Stack<T>::size() const noexcept {
    return data_.size();
}

template <typename T>
bool Stack<T>::empty() const noexcept {
    return data_.empty();
}

// ### Access methods ###

template <typename T>
const T& Stack<T>::top() const {
    if (empty()) throw std::out_of_range("top on empty stack");
    return data_.back();
}

template <typename T>
T& Stack<T>::top() {
    if (empty()) throw std::out_of_range("top on empty stack");
    return data_.back();
}

// ### Modifier methods ###

template <typename T>
void Stack<T>::push(const T& element) {
    data_.push_back(element);
}

template <typename T>
void Stack<T>::push(T&& element) {
    data_.push_back(std::move(element));
}

template <typename T>
template <class... Args>
void Stack<T>::emplace(Args&&... args) {
    data_.emplace_back(std::forward<Args>(args)...);
}

template <typename T>
T Stack<T>::pop() {
    if (empty()) throw std::out_of_range("pop on empty stack");

    T value = std::move(data_.back());
    data_.pop_back();

    return value;
}

template <typename T>
void Stack<T>::clear() noexcept {
    data_.clear();
}

// ### Operators ###

template <typename T>
bool Stack<T>::operator==(const Stack<T>& other) const {
    return this->data_ == other.data_;
}

template <typename T>
bool Stack<T>::operator!=(const Stack& other) const {
    return this->data_ != other.data_;
}

// ### Swap methods ###

template <typename T>
void Stack<T>::swap(Stack& other) noexcept {
    data_.swap(other.data_);
}

template <typename T>
void swap(Stack<T>& a, Stack<T>& b) noexcept {
    a.swap(b);
}
