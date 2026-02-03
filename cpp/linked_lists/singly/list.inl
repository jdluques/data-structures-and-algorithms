#include "list.hpp"

#include <stdexcept>

// ### Iteration ###

template <typename T>
SinglyLinkedList<T>::iterator
SinglyLinkedList<T>::begin() const noexcept {
    return iterator(head_);
}

template <typename T>
SinglyLinkedList<T>::iterator
SinglyLinkedList<T>::end() const noexcept {
    return iterator(nullptr);
}

template <typename T>
SinglyLinkedList<T>::const_iterator
SinglyLinkedList<T>::cbegin() const noexcept {
    return const_iterator(head_);
}

template <typename T>
SinglyLinkedList<T>::const_iterator
SinglyLinkedList<T>::cend() const noexcept {
    return const_iterator(nullptr);
}

// ### Constructors ###

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList& other) {
    for (Node* n = other.head_; n; n = n->next) {
        push_back(n->value);
    }
}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(SinglyLinkedList&& other) noexcept : head_(other.head_), size_(other.size_) {
    other.head_ = nullptr;
    other.size_ = 0;
}

// ### Destructor ###

template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList() noexcept { clear(); }

// ### = operator ###

template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(SinglyLinkedList& other) {
    if (this != &other) {
        clear();
        for (Node* n = other.head_; n; n = n->next) push_back(n->value);
    }
    return *this;
}

template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(SinglyLinkedList&& other) {
    if (this != &other) {
        clear();
        head_ = other.head_;
        size_ = other.size_;

        other.head_ = nullptr;
        other.size_ = 0;
    }
    return *this;
}

// ### Capacity methods ###

template <typename T>
std::size_t SinglyLinkedList<T>::size() const noexcept { return size_; }

template <typename T>
bool SinglyLinkedList<T>::empty() const noexcept { return size() == 0; }

// ### Element access methods ###

template <typename T>
T& SinglyLinkedList<T>::front() const {
    if (empty()) throw std::out_of_range("front on empty list");
    return head_->value;
}

template <typename T>
T& SinglyLinkedList<T>::back() const {
    if (empty()) throw std::out_of_range("back on empty list");
    
    Node* curr = head_;
    while (curr->next) curr = curr->next;
    return curr->value;
}

template <typename T>
T& SinglyLinkedList<T>::at(std::size_t pos) const {
    if (pos > size()) throw std::out_of_range("at pos out of range");
    
    Node* curr = head_;
    while (pos--) curr = curr->next;
    return curr->value;
}

template <typename T>
T& SinglyLinkedList<T>::operator[](std::size_t pos) const {
    if (pos > size()) throw std::out_of_range("[pos] out of range");
    
    Node* curr = head_;
    while (pos--) curr = curr->next;
    return curr->value;
}

template <typename T>
SinglyLinkedList<T>::Node* SinglyLinkedList<T>::find(const T& value) const {
    for (Node* curr = head_; curr; curr = curr->next) {
        if (curr->value == value) return curr;
    }
    return nullptr;
}

// ### Modifier methods ###

template <typename T>
void SinglyLinkedList<T>::push_front(const T& value) {
    head_ = new Node(value, head_);
    if (!tail_) tail_ = head_;
    size_++;
}

template <typename T>
void SinglyLinkedList<T>::push_back(const T& value) {
    if (tail_) {
        tail_->next = new Node(value);
        tail_ = tail_->next;
    } else {
        tail_ = head_ = new Node(value);
    }

    size_++;
}

template <typename T>
void SinglyLinkedList<T>::insert(const T& value, std::size_t pos) {
    if (pos >= size()) throw std::out_of_range("insert pos out of range");

    if (pos == 0) this->push_front(value);
    else if (pos == size()) this->push_back(value);
    else {
        Node* curr = head_;
        while (--pos) curr = curr->next;

        Node* newNode = new Node(value, curr->next);
        curr->next = newNode;

        size_++;
    }
}

template <typename T>
void SinglyLinkedList<T>::pop_front() {
    if (empty()) throw std::out_of_range("pop_front on empty list");

    Node* oldHead = head_;
    head_ = head_->next;
    delete oldHead;
    size_--;

    if (empty()) tail_ = nullptr;
}

template <typename T>
void SinglyLinkedList<T>::pop_back() {
    if (empty()) throw std::out_of_range("pop_back on empty list");

    if (size() == 1) {
        delete head_;
        head_ = tail_ = nullptr;
    } else {
        Node* curr = head_;
        while (curr->next != tail_) curr = curr->next;
        delete tail_;
        tail_ = curr;
        tail_->next = nullptr;
    }

    size_--;
}

template <typename T>
void SinglyLinkedList<T>::erase(std::size_t pos) {
    if (pos > size()) throw std::out_of_range("erase pos out of range");

    if (pos == 0) this->pop_front();
    else if (pos == size()-1) this->pop_back();
    else {
        Node* curr = head_;
        while (--pos) curr = curr->next;

        Node* nodeToDelete = curr->next;
        curr->next = nodeToDelete->next;
        delete nodeToDelete;

        size_--;
    }
}

template <typename T>
void SinglyLinkedList<T>::clear() {
    while (!empty()) pop_front();
}
