#pragma once

#include "doubly.hpp"

#include <stdexcept>

namespace ds {
    // ### Iteration ###

    template <typename T>
    ds::DoublyLinkedList<T>::iterator
    ds::DoublyLinkedList<T>::begin() const noexcept {
        return iterator(head_);
    }

    template <typename T>
    ds::DoublyLinkedList<T>::iterator
    ds::DoublyLinkedList<T>::end() const noexcept {
        return iterator(nullptr);
    }

    template <typename T>
    ds::DoublyLinkedList<T>::const_iterator
    ds::DoublyLinkedList<T>::cbegin() const noexcept {
        return const_iterator(head_);
    }

    template <typename T>
    ds::DoublyLinkedList<T>::const_iterator
    ds::DoublyLinkedList<T>::cend() const noexcept {
        return const_iterator(nullptr);
    }

    // ### Constructors ###

    template <typename T>
    ds::DoublyLinkedList<T>::DoublyLinkedList(const ds::DoublyLinkedList<T>& other) {
        for (Node* n = other.head_; n; n = n->next_) {
            push_back(n->value_);
        }
    }

    template <typename T>
    ds::DoublyLinkedList<T>::DoublyLinkedList(ds::DoublyLinkedList<T>&& other) noexcept : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0;
    }

    // ### Destructor ###

    template <typename T>
    ds::DoublyLinkedList<T>::~DoublyLinkedList() noexcept { clear(); }

    // ### = operator ###

    template <typename T>
    ds::DoublyLinkedList<T>& ds::DoublyLinkedList<T>::operator=(ds::DoublyLinkedList<T>& other) {
        if (this != &other) {
            clear();
            for (Node* n = other.head_; n; n = n->next_) push_back(n->value_);
        }
        return *this;
    }

    template <typename T>
    ds::DoublyLinkedList<T>& ds::DoublyLinkedList<T>::operator=(ds::DoublyLinkedList<T>&& other) {
        if (this != &other) {
            clear();
            head_ = other.head_;
            tail_ = other.tail_;
            size_ = other.size_;

            other.head_ = nullptr;
            other.tail_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    // ### Capacity methods ###

    template <typename T>
    std::size_t ds::DoublyLinkedList<T>::size() const noexcept { return size_; }

    template <typename T>
    bool ds::DoublyLinkedList<T>::empty() const noexcept { return size() == 0; }

    // ### Element access methods ### 

    template <typename T>
    T const & ds::DoublyLinkedList<T>::front() const {
        if (empty()) throw std::out_of_range("front on empty list");
        return head_->value_;
    }

    template <typename T>
    T& ds::DoublyLinkedList<T>::front() {
        if (empty()) throw std::out_of_range("front on empty list");
        return head_->value_;
    }

    template <typename T>
    T const& ds::DoublyLinkedList<T>::back() const {
        if (empty()) throw std::out_of_range("back on empty list");
        return tail_->value_;
    } 

    template <typename T>
    T& ds::DoublyLinkedList<T>::back() {
        if (empty()) throw std::out_of_range("back on empty list");
        return tail_->value_;
    }

    template <typename T>
    typename DoublyLinkedList<T>::Node* DoublyLinkedList<T>::node_at(std::size_t pos) const {
        if (pos >= size_) throw std::out_of_range("position out of range");

        Node* curr;
        if (pos < size_/2) {
            curr = head_;
            while (pos--) curr = curr->next_;
        } else {
            pos = size_ - 1 - pos;
            curr = tail_;
            while (pos--) curr = curr->prev_;
        }

        return curr;
    }

    template <typename T>
    T const& ds::DoublyLinkedList<T>::at(std::size_t pos) const {
        return node_at(pos)->value_;
    } 

    template <typename T>
    T& ds::DoublyLinkedList<T>::at(std::size_t pos) {
        return node_at(pos)->value_;
    }

    template <typename T>
    T const& ds::DoublyLinkedList<T>::operator[](std::size_t pos) const {
        return node_at(pos)->value_;
    }

    template <typename T>
    T& ds::DoublyLinkedList<T>::operator[](std::size_t pos) {
        return node_at(pos)->value_;
    }

    template <typename T>
    ds::DoublyLinkedList<T>::Node* ds::DoublyLinkedList<T>::find(T const& value) const {
        for (Node* curr = head_; curr; curr = curr->next_) {
            if (curr->value_ == value) return curr;
        }
        return nullptr;
    }

    // ### Modifier methods ###

    template <typename T>
    void ds::DoublyLinkedList<T>::push_front(T const& value) {
        head_ = new Node(value, head_);
        if (!tail_) tail_ = head_;
        size_++;
    }

    template <typename T>
    void ds::DoublyLinkedList<T>::push_back(T const& value) {
        if (tail_) {
            tail_->next_ = new Node(value);
            tail_ = tail_->next_;
        } else {
            tail_ = head_ = new Node(value);
        }

        size_++;
    }

    template <typename T>
    void ds::DoublyLinkedList<T>::insert(T const& value, std::size_t pos) {
        if (pos > size()) throw std::out_of_range("insert pos out of range");

        if (pos == 0) this->push_front(value);
        else if (pos == size()) this->push_back(value);
        else {
            Node* curr = head_;
            while (--pos) curr = curr->next_;

            Node* newNode = new Node(value, curr->next_);
            curr->next_ = newNode;

            size_++;
        }
    }

    template <typename T>
    void ds::DoublyLinkedList<T>::pop_front() {
        if (empty()) throw std::out_of_range("pop_front on empty list");

        Node* oldHead = head_;
        head_ = head_->next_;
        delete oldHead;
        size_--;

        if (empty()) tail_ = nullptr;
    }

    template <typename T>
    void ds::DoublyLinkedList<T>::pop_back() {
        if (empty()) throw std::out_of_range("pop_back on empty list");

        if (size() == 1) {
            delete head_;
            head_ = tail_ = nullptr;
        } else {
            Node* curr = head_;
            while (curr->next_ != tail_) curr = curr->next_;
            delete tail_;
            tail_ = curr;
            tail_->next_ = nullptr;
        }

        size_--;
    }

    template <typename T>
    void ds::DoublyLinkedList<T>::erase(std::size_t pos) {
        if (pos > size()) throw std::out_of_range("erase pos out of range");

        if (pos == 0) this->pop_front();
        else if (pos == size()-1) this->pop_back();
        else {
            Node* curr = head_;
            while (--pos) curr = curr->next_;

            Node* nodeToDelete = curr->next_;
            curr->next_ = nodeToDelete->next_;
            delete nodeToDelete;

            size_--;
        }
    }

    template <typename T>
    void ds::DoublyLinkedList<T>::clear() {
        while (!empty()) pop_front();
    }

    // ### Sort method and helpers ###

    template <typename T>
    void ds::DoublyLinkedList<T>::sort() {
        head_ = sort_list(head_);
    }

    template <typename T>
    ds::DoublyLinkedList<T>::Node*
    ds::DoublyLinkedList<T>::sort_list(Node* head) {
        if (!head || !head->next_) return head;

        Node* middle = find_middle(head);
        Node* rightHead = middle->next_;
        middle->next_ = nullptr;

        Node* sortedLeftHead = sort_list(head);
        Node* sortedRightHead = sort_list(rightHead);

        return merge(sortedLeftHead, sortedRightHead);
    }

    template <typename T>
    ds::DoublyLinkedList<T>::Node*
    ds::DoublyLinkedList<T>::merge(Node* head1, Node* head2) {
        Node* dummy = new Node(T());
        Node* curr = dummy;

        while (head1 && head2) {
            if (head1->value_ <= head2->value_) {
                curr->next_ = head1;
                head1 = head1->next_;
            } else {
                curr->next_ = head2;
                head2 = head2->next_;
            }

            curr = curr->next_;
        }

        if (head1) curr->next_ = head1;
        else if (head2) curr->next_ = head2;

        Node* sortedHead = dummy->next_;
        delete dummy;

        return sortedHead;
    }

    template <typename T>
    ds::DoublyLinkedList<T>::Node*
    ds::DoublyLinkedList<T>::find_middle(Node* head) {
        if (!head) return nullptr;

        Node* slow = head;
        Node* fast = head->next_;

        while (fast && fast->next_) {
            slow = slow->next_;
            fast = fast->next_->next_;
        }

        return slow;
    }

}
