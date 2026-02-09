#pragma once

#include <cstddef>

template <typename T>
class SinglyLinkedList {
private:
    struct Node {
        T value;
        Node* next = nullptr;

        explicit Node(const T& v, Node* n = nullptr) : value(v), next(n) {}

        bool operator<(const Node& other) const {
            return this->value < other.value;
        }
    };

    Node* head_ = nullptr;
    Node* tail_ = nullptr;
    std::size_t size_ = 0;

    // Sort helpers
    Node* sortList(Node* head);
    Node* merge(Node* head1, Node* head2);
    Node* findMiddle(Node* head);
public:
    class iterator {
    private:
        Node* current_;
        friend class const_iterator;
    public:
        explicit iterator(Node* node = nullptr) noexcept : current_(node) {}

        T& operator*() const { return current_->value; }
        T& operator->() const { return &current_->value; }

        iterator& operator++() {
            current_ = current_->next;
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

        T& operator*() const { return current_->value; }
        T* operator->() const { return &current_->value; }

        const_iterator& operator++() {
            current_ = current_->next;
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

    SinglyLinkedList() = default;
    SinglyLinkedList(const SinglyLinkedList& other);
    SinglyLinkedList(SinglyLinkedList&& other) noexcept;

    ~SinglyLinkedList() noexcept;
    
    SinglyLinkedList& operator=(SinglyLinkedList& other);
    SinglyLinkedList& operator=(SinglyLinkedList&& other);

    std::size_t size() const noexcept;
    bool empty() const noexcept;

    T& front() const;
    T& back() const;

    T& at(std::size_t pos) const;
    T& operator[](std::size_t pos) const;

    Node* find(const T& value) const;

    void push_front(const T& value);
    void push_back(const T& value);
    void insert(const T& value, std::size_t pos);

    void pop_front();
    void pop_back();
    void erase(std::size_t pos);

    void clear();

    void sort();
};
