#pragma once

#include "stack.hpp"

#include <stdexcept>

namespace ds {
    // ### Capacity methods ###

    template <typename T>
    std::size_t ds::Stack<T>::size() const noexcept {
        return data_.size();
    }

    template <typename T>
    bool ds::Stack<T>::empty() const noexcept {
        return data_.empty();
    }

    // ### Access methods ###

    template <typename T>
    T const& ds::Stack<T>::top() const {
        if (empty()) throw std::out_of_range("top on empty stack");
        return data_.back();
    }

    template <typename T>
    T& ds::Stack<T>::top() {
        if (empty()) throw std::out_of_range("top on empty stack");
        return data_.back();
    }

    // ### Modifier methods ###

    template <typename T>
    void ds::Stack<T>::push(T const& element) {
        data_.push_back(element);
    }

    template <typename T>
    void ds::Stack<T>::push(T&& element) {
        data_.push_back(std::move(element));
    }

    template <typename T>
    template <class... Args>
    void ds::Stack<T>::emplace(Args&&... args) {
        data_.emplace_back(std::forward<Args>(args)...);
    }

    template <typename T>
    T ds::Stack<T>::pop() {
        if (empty()) throw std::out_of_range("pop on empty stack");

        T value = std::move(data_.back());
        data_.pop_back();

        return value;
    }

    template <typename T>
    void ds::Stack<T>::clear() noexcept {
        data_.clear();
    }

    // ### Operators ###

    template <typename T>
    bool ds::Stack<T>::operator==(const ds::Stack<T>& other) const {
        return this->data_ == other.data_;
    }

    template <typename T>
    bool ds::Stack<T>::operator!=(const ds::Stack<T>& other) const {
        return this->data_ != other.data_;
    }

    // ### Swap methods ###

    template <typename T>
    void ds::Stack<T>::swap(ds::Stack<T>& other) noexcept {
        data_.swap(other.data_);
    }

    template <typename T>
    void swap(ds::Stack<T>& a, ds::Stack<T>& b) noexcept {
        a.swap(b);
    }

}
