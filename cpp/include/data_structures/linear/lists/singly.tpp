#pragma once

#include "singly.hpp"

#include <stdexcept>

namespace ds {
    // ### Iteration ###

    template <typename T>
    ds::SinglyLinkedList<T>::iterator
    ds::SinglyLinkedList<T>::begin() const noexcept {
        return iterator(sentinel_);
    }

    template <typename T>
    ds::SinglyLinkedList<T>::iterator
    ds::SinglyLinkedList<T>::end() const noexcept {
        return iterator(nullptr);
    }

    template <typename T>
    ds::SinglyLinkedList<T>::const_iterator
    ds::SinglyLinkedList<T>::cbegin() const noexcept {
        return const_iterator(sentinel_);
    }

    template <typename T>
    ds::SinglyLinkedList<T>::const_iterator
    ds::SinglyLinkedList<T>::cend() const noexcept {
        return const_iterator(nullptr);
    }

    // ### Constructors ###

    template <typename T>
    ds::SinglyLinkedList<T>::SinglyLinkedList(const ds::SinglyLinkedList<T>& other) {
        for (Node* n = other.sentinel_->next_; n; n = n->next_) {
            this->push_back(n->value_);
        }
    }

    template <typename T>
    ds::SinglyLinkedList<T>::SinglyLinkedList(ds::SinglyLinkedList<T>&& other) noexcept : sentinel_(other.sentinel_), tail_(other.tail_), size_(other.size_) {
        other.sentinel_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0;
    }

    // ### Destructor ###

    template <typename T>
    ds::SinglyLinkedList<T>::~SinglyLinkedList() noexcept { clear(); }

    // ### = operator ###

    template <typename T>
    ds::SinglyLinkedList<T>& ds::SinglyLinkedList<T>::operator=(ds::SinglyLinkedList<T>& other) {
        if (this != &other) {
            this->clear();
            for (Node* n = other.sentinel_->next_; n; n = n->next_) this->push_back(n->value_);
        }
        return *this;
    }

    template <typename T>
    ds::SinglyLinkedList<T>& ds::SinglyLinkedList<T>::operator=(ds::SinglyLinkedList<T>&& other) {
        if (this != &other) {
            clear();
            this->sentinel_ = other.sentinel_;
            this->tail_ = other.tail_;
            this->size_ = other.size_;

            other.sentinel_ = nullptr;
            other.tail_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    // ### Capacity methods ###

    template <typename T>
    std::size_t ds::SinglyLinkedList<T>::size() const noexcept { return size_; }

    template <typename T>
    bool ds::SinglyLinkedList<T>::empty() const noexcept { return size_ == 0; }

    // ### Element access methods ###

    template <typename T>
    T const& ds::SinglyLinkedList<T>::front() const {
        if (empty()) throw std::out_of_range("front on empty list");
        return sentinel_->next_->value_;
    } 

    template <typename T>
    T& ds::SinglyLinkedList<T>::front() {
        if (empty()) throw std::out_of_range("front on empty list");
        return sentinel_->next_->value_;
    }

    template <typename T>
    T const& ds::SinglyLinkedList<T>::back() const {
        if (empty()) throw std::out_of_range("back on empty list");
        return tail_->value_;
    }

    template <typename T>
    T& ds::SinglyLinkedList<T>::back() {
        if (empty()) throw std::out_of_range("back on empty list");
        return tail_->value_;
    }

    template <typename T>
    SinglyLinkedList<T>::Node* ds::SinglyLinkedList<T>::node_at(std::size_t pos) {
        if (pos >= size_) throw std::out_of_range("at pos out of range");
        
        if (pos == 0) return sentinel_->next_;
        else if (pos == size_-1) return tail_;
        else {
            Node* curr = sentinel_->next_;
            while (pos--) curr = curr->next_;
            return curr;
        }
    }

    template <typename T>
    T const& ds::SinglyLinkedList<T>::at(std::size_t pos) const {
        return node_at(pos)->value_;
    }

    template <typename T>
    T& ds::SinglyLinkedList<T>::at(std::size_t pos) {
        return node_at(pos)->value_;
    }

    template <typename T>
    T const& ds::SinglyLinkedList<T>::operator[](std::size_t pos) const {
        return node_at(pos)->value_;
    }

    template <typename T>
    T& ds::SinglyLinkedList<T>::operator[](std::size_t pos) {
        return node_at(pos)->value_;
    }

    template <typename T>
    ds::SinglyLinkedList<T>::Node* ds::SinglyLinkedList<T>::find(T const& value) const {
        for (Node* curr = sentinel_->next_; curr; curr = curr->next_) {
            if (curr->value_ == value) return curr;
        }
        return nullptr;
    }

    // ### Modifier methods ###

    template <typename T>
    void ds::SinglyLinkedList<T>::push_front(T const& value) {
        sentinel_->next_ = new Node(value, sentinel_->next_);
        if (size_ == 0) tail_ = sentinel_->next_;
        size_++;
    }

    template <typename T>
    void ds::SinglyLinkedList<T>::push_back(T const& value) {
        tail_->next_ = new Node(value);
        tail_ = tail_->next_;
        size_++;
    }

    template <typename T>
    void ds::SinglyLinkedList<T>::insert(T const& value, std::size_t pos) {
        if (pos > size()) throw std::out_of_range("insert pos out of range");

        if (pos == 0) this->push_front(value);
        else if (pos == size()) this->push_back(value);
        else {
            Node* curr = sentinel_;
            while (pos--) curr = curr->next_;

            Node* newNode = new Node(value, curr->next_);
            curr->next_ = newNode;

            size_++;
        }
    }

    template <typename T>
    T& ds::SinglyLinkedList<T>::pop_front() {
        if (empty()) throw std::out_of_range("pop_front on empty list");

        Node* prevFront = sentinel_->next_;
        T& prevFrontValue = prevFront->value_;
        sentinel_->next_ = prevFront->next_;
        if (prevFront == tail_) tail_ = sentinel_;
        delete prevFront;

        size_--;

        return prevFrontValue;
    }

    template <typename T>
    T& ds::SinglyLinkedList<T>::pop_back() {
        if (empty()) throw std::out_of_range("pop_back on empty list");

        Node* curr = sentinel_;
        while (curr->next_ != tail_) curr = curr->next_;

        T& prevTailValue = tail_->value_;
        delete tail_;
        tail_ = curr;
        tail_->next_ = nullptr;
        
        size_--;

        return prevTailValue;
    }

    template <typename T>
    T& ds::SinglyLinkedList<T>::erase(std::size_t pos) {
        if (pos > size()) throw std::out_of_range("erase pos out of range");

        if (pos == 0) return this->pop_front();
        else if (pos == size()-1) return this->pop_back();
        else {
            Node* curr = sentinel_;
            while (pos--) curr = curr->next_;

            Node* nodeToDelete = curr->next_;
            T& deletedNodeValue = nodeToDelete->value_;
            curr->next_ = nodeToDelete->next_;
            delete nodeToDelete;

            size_--;

            return deletedNodeValue;
        }
    }

    template <typename T>
    void ds::SinglyLinkedList<T>::clear() {
        while (size_ != 0) pop_front();
    }

    // ### Sort method and helpers ###

    template <typename T>
    void ds::SinglyLinkedList<T>::sort() {
        sentinel_ = sort_list(sentinel_->next_);

        Node* curr = sentinel_;
        while (curr && curr->next_) curr = curr->next_;
        tail_ = curr;
    }

    template <typename T>
    ds::SinglyLinkedList<T>::Node*
    ds::SinglyLinkedList<T>::sort_list(Node* head) {
        if (!head || !head->next_) return head;

        Node* middle = find_middle(head);
        Node* rightHead = middle->next_;
        middle->next_ = nullptr;

        Node* sortedLeftHead = sort_list(head);
        Node* sortedRightHead = sort_list(rightHead);

        return merge(sortedLeftHead, sortedRightHead);
    }

    template <typename T>
    ds::SinglyLinkedList<T>::Node*
    ds::SinglyLinkedList<T>::merge(Node* head1, Node* head2) {
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
    ds::SinglyLinkedList<T>::Node*
    ds::SinglyLinkedList<T>::find_middle(Node* head) {
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
