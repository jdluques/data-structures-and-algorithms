#pragma once

#include <functional>
#include <vector>

namespace ds {

    template <typename T, typename Compare = std::greater<T>>
    class Heap {
    private:
        std::vector<T> data_;

        Compare comp_;

        std::size_t last_internal_node() const;

        std::size_t parent(std::size_t idx) const;
        std::size_t right(std::size_t idx) const;
        std::size_t left(std::size_t idx) const;

        void heapify_up(size_t idx);
        void heapify_down(size_t idx);
    
    public:
        Heap() = default;
        Heap(std::vector<T> data);
        ~Heap() = default;

        bool empty() const noexcept;

        std::size_t size() const noexcept;

        T const& peek() const;
        T& peek();

        void push(T const& value);

        T pop();

        void clear();
    };

}

#include "heap.tpp"
