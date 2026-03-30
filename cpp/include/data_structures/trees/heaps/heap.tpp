#pragma once

#include "heap.hpp"

#include <algorithm>
#include <cstddef>
#include <cwchar>
#include <stdexcept>
#include <utility>
#include <vector>

namespace ds {

    template <typename T, typename Compare>
    std::size_t Heap<T, Compare>::last_internal_node() const {
        if (data_.size() < 2) return 0;
        return data_.size() / 2 - 1;
    }

    template <typename T, typename Compare>
    std::size_t Heap<T, Compare>::parent(std::size_t idx) const {
        return (idx - 1) / 2;
    }

    template <typename T, typename Compare>
    std::size_t Heap<T, Compare>::left(std::size_t idx) const {
        return (2 * idx) + 1;
    }

    template <typename T, typename Compare>
    std::size_t Heap<T, Compare>::right(std::size_t idx) const {
        return (2 * idx) + 2;
    }

    template <typename T, typename Compare>
    void Heap<T, Compare>::heapify_up(size_t idx) {
        if (idx == 0) return;

        if (comp_(data_[idx], data_[parent(idx)])) {
            std::swap(data_[idx], data_[parent(idx)]);
            heapify_up(parent(idx));
        }
    }

    template <typename T, typename Compare>
    void Heap<T, Compare>::heapify_down(size_t idx) {
        size_t largest = idx;

        if (left(idx) < size() && comp_(data_[left(idx)], data_[largest]))
            largest = left(idx);

        if (right(idx) < size() && comp_(data_[right(idx)], data_[largest]))
            largest = right(idx);

        if (largest != idx) {
            std::swap(data_[idx], data_[largest]);
            heapify_down(largest);
        }
    }

    template <typename T, typename Compare>
    Heap<T, Compare>::Heap(std::vector<T> data) : data_(std::move(data)) {
        for (size_t i = last_internal_node()+1; i > 0; i--)
            heapify_down(i-1);
    }

    template <typename T, typename Compare>
    bool Heap<T, Compare>::empty() const noexcept {
        return data_.empty();
    }

    template <typename T, typename Compare>
    std::size_t Heap<T, Compare>::size() const noexcept {
        return data_.size();
    }

    template <typename T, typename Compare>
    T const& Heap<T, Compare>::peek() const {
        if (empty()) throw std::out_of_range("heap is empty");
        return data_[0];
    }

    template <typename T, typename Compare>
    T& Heap<T, Compare>::peek() {
        if (empty()) throw std::out_of_range("heap is empty");
        return data_[0];
    }

    template <typename T, typename Compare>
    void Heap<T, Compare>::push(T const& value) {
        data_.push_back(value);
        heapify_up(size()-1);
    }

    template <typename T, typename Compare>
    T Heap<T, Compare>::pop() {
        if (empty()) throw std::out_of_range("heap is empty");

        T prevTopValue = std::move(data_[0]);
        data_[0] = data_.back();
        data_.pop_back();
        
        if (!empty()) heapify_down(0);

        return prevTopValue;
    }

    template <typename T, typename Compare>
    void Heap<T, Compare>::clear() {
        data_.clear();
    }

}
