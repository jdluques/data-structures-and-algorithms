#pragma once

#include <cstddef>

namespace ds {

    template <typename T>
    class DoublyLinkedList {
    private:
        struct Node {
            T value_;
            Node* next_ = nullptr;
            Node* prev_ = nullptr;

            explicit Node(T const& v, Node* n = nullptr) : value_(v), next_(n) {}

            bool operator<(const Node& other) const {
                return this->value_ < other.value_;
            }
        };

        Node* head_ = nullptr;
        Node* tail_ = nullptr;
        std::size_t size_ = 0;

        // Sort helpers
        Node* sort_list(Node* head);
        Node* merge(Node* head1, Node* head2);
        Node* find_middle(Node* head);

        // Access helper
        Node* node_at(std::size_t pos) const;
    public:
        class iterator {
        private:
            Node* current_;
            friend class const_iterator;
        public:
            explicit iterator(Node* node = nullptr) noexcept : current_(node) {}

            T& operator*() { return current_->value_; }
            T& operator->() { return &current_->value_; }

            iterator& operator++() {
                current_ = current_->next_;
                return *this;
            }

            iterator operator++(int) {
                iterator tmp(this);
                (*this)++;
                return tmp;
            }

            friend bool operator==(const iterator& a, const iterator& b) { return a.current_ == b.current_; }
            friend bool operator!=(const iterator& a, const iterator& b) { return a.current_ != b.current_; }
        };

        class const_iterator {
        private:
            const Node* current_;
        public:
            explicit const_iterator(const Node* node = nullptr) noexcept : current_(node) {}
            const_iterator(const iterator& it) noexcept : current_(it.current_) {}

            T const& operator*() const { return current_->value_; }
            T const* operator->() const { return &current_->value_; }

            const_iterator& operator++() {
                current_ = current_->next_;
                return *this;
            }

            const_iterator operator++(int) {
                const_iterator tmp(this);
                (*this)++;
                return tmp;
            }

            friend bool operator==(const const_iterator& a, const const_iterator& b) { return a.current_ == b.current_; }
            friend bool operator!=(const const_iterator& a, const const_iterator& b) { return a.current_ != b.current_; }
        };

        iterator begin() const noexcept;
        iterator end() const noexcept;
        const_iterator cbegin() const noexcept;
        const_iterator cend() const noexcept;

        DoublyLinkedList() = default;
        DoublyLinkedList(const DoublyLinkedList& other);
        DoublyLinkedList(DoublyLinkedList&& other) noexcept;

        ~DoublyLinkedList() noexcept;
        
        DoublyLinkedList& operator=(DoublyLinkedList& other);
        DoublyLinkedList& operator=(DoublyLinkedList&& other);

        std::size_t size() const noexcept;
        bool empty() const noexcept;

        T const& front() const; 
        T& front();

        T const& back() const;
        T& back();

        T const& at(std::size_t pos) const;
        T& at(std::size_t pos);

        T const& operator[](std::size_t pos) const;
        T& operator[](std::size_t pos);

        Node* find(T const& value) const;

        void push_front(T const& value);
        void push_back(T const& value);
        void insert(T const& value, std::size_t pos);

        void pop_front();
        void pop_back();
        void erase(std::size_t pos);

        void clear();

        void sort();
    };

}

#include "doubly.tpp"
