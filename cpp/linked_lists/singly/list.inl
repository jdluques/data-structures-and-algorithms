#include "list.hpp"

#include <stdexcept>

// ### Iteration ###

template <typename T>
SinglyLinkedList<T>::iterator
SinglyLinkedList<T>::begin() const noexcept {
    return iterator(sentinel_);
}

template <typename T>
SinglyLinkedList<T>::iterator
SinglyLinkedList<T>::end() const noexcept {
    return iterator(nullptr);
}

template <typename T>
SinglyLinkedList<T>::const_iterator
SinglyLinkedList<T>::cbegin() const noexcept {
    return const_iterator(sentinel_);
}

template <typename T>
SinglyLinkedList<T>::const_iterator
SinglyLinkedList<T>::cend() const noexcept {
    return const_iterator(nullptr);
}

// ### Constructors ###

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList& other) {
    for (Node* n = other.sentinel_; n; n = n->next) {
        this->push_back(n->value);
    }
}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(SinglyLinkedList&& other) noexcept : sentinel_(other.sentinel_), tail_(other.tail_), size_(other.size_) {
    other.sentinel_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
}

// ### Destructor ###

template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList() noexcept { clear(); }

// ### = operator ###

template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(SinglyLinkedList& other) {
    if (this != &other) {
        this->clear();
        for (Node* n = other.sentinel_; n; n = n->next) this->push_back(n->value);
    }
    return *this;
}

template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(SinglyLinkedList&& other) {
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
std::size_t SinglyLinkedList<T>::size() const noexcept { return size_; }

template <typename T>
bool SinglyLinkedList<T>::empty() const noexcept { return size_ == 0; }

// ### Element access methods ###

template <typename T>
T& SinglyLinkedList<T>::front() const {
    if (empty()) throw std::out_of_range("front on empty list");
    return sentinel_->value;
}

template <typename T>
T& SinglyLinkedList<T>::back() const {
    if (empty()) throw std::out_of_range("back on empty list");
    return tail_->value;
}

template <typename T>
T& SinglyLinkedList<T>::at(std::size_t pos) const {
    if (pos >= size_) throw std::out_of_range("at pos out of range");
    
    if (pos == 0) return front();
    else if (pos == size_-1) return back();
    else {
        Node* curr = sentinel_;
        while (pos--) curr = curr->next;
        return curr->value;
    }
}

template <typename T>
T& SinglyLinkedList<T>::operator[](std::size_t pos) const {
    if (pos > size()) throw std::out_of_range("[pos] out of range");
    
    if (pos == 0) return front();
    else if (pos == size_-1) return back();
    else {
        Node* curr = sentinel_;
        while (pos--) curr = curr->next;
        return curr->value;
    }
}

template <typename T>
SinglyLinkedList<T>::Node* SinglyLinkedList<T>::find(const T& value) const {
    for (Node* curr = sentinel_; curr; curr = curr->next) {
        if (curr->value == value) return curr;
    }
    return nullptr;
}

// ### Modifier methods ###

template <typename T>
void SinglyLinkedList<T>::push_front(const T& value) {
    sentinel_->next = new Node(value, sentinel_->next);
    if (size_ == 0) tail_ = sentinel_->next;
    size_++;
}

template <typename T>
void SinglyLinkedList<T>::push_back(const T& value) {
    tail_->next = new Node(value);
    tail_ = tail_->next;
    size_++;
}

template <typename T>
void SinglyLinkedList<T>::insert(const T& value, std::size_t pos) {
    if (pos >= size()) throw std::out_of_range("insert pos out of range");

    if (pos == 0) this->push_front(value);
    else if (pos == size()) this->push_back(value);
    else {
        Node* curr = sentinel_;
        while (pos--) curr = curr->next;

        Node* newNode = new Node(value, curr->next);
        curr->next = newNode;

        size_++;
    }
}

template <typename T>
T& SinglyLinkedList<T>::pop_front() {
    if (empty()) throw std::out_of_range("pop_front on empty list");

    Node* prevFront = sentinel_->next;
    T* prevFrontValue = prevFront->value;
    sentinel_->next = prevFront->next;
    if (prevFront == tail_) tail_ = sentinel_;
    delete prevFront;

    size_--;

    return prevFrontValue;
}

template <typename T>
T& SinglyLinkedList<T>::pop_back() {
    if (empty()) throw std::out_of_range("pop_back on empty list");

    Node* curr = sentinel_;
    while (curr->next != tail_) curr = curr->next;

    T* prevTailValue = tail_->value;
    delete tail_;
    tail_ = curr;
    tail_->next = nullptr;
    
    size_--;

    return prevTailValue;
}

template <typename T>
T& SinglyLinkedList<T>::erase(std::size_t pos) {
    if (pos > size()) throw std::out_of_range("erase pos out of range");

    if (pos == 0) return this->pop_front();
    else if (pos == size()-1) return this->pop_back();
    else {
        Node* curr = sentinel_;
        while (pos--) curr = curr->next;

        Node* nodeToDelete = curr->next;
        T* deletedNodeValue = nodeToDelete->value;
        curr->next = nodeToDelete->next;
        delete nodeToDelete;

        size_--;

        return deletedNodeValue;
    }
}

template <typename T>
void SinglyLinkedList<T>::clear() {
    while (size_ != 0) pop_front();
}

// ### Sort method and helpers ###

template <typename T>
void SinglyLinkedList<T>::sort() {
    sentinel_ = sortList(sentinel_->next);

    Node* curr = sentinel_;
    while (curr && curr->next) curr = curr->next;
    tail_ = curr;
}

template <typename T>
SinglyLinkedList<T>::Node*
SinglyLinkedList<T>::sortList(Node* head) {
    if (!head || !head->next) return head;

    Node* middle = findMiddle(head);
    Node* rightHead = middle->next;
    middle->next = nullptr;

    Node* sortedLeftHead = sortList(head);
    Node* sortedRightHead = sortList(rightHead);

    return merge(sortedLeftHead, sortedRightHead);
}

template <typename T>
SinglyLinkedList<T>::Node*
SinglyLinkedList<T>::merge(Node* head1, Node* head2) {
    Node* dummy = new Node(T());
    Node* curr = dummy;

    while (head1 && head2) {
        if (head1->value <= head2->data) {
            curr->next = head1;
            head1 = head1->next;
        } else {
            curr->next = head2;
            head2 = head2->next;
        }

        curr = curr->next;
    }

    if (head1) curr->next = head1;
    else if (head2) curr->next = head2;

    Node* sortedHead = dummy->next;
    delete dummy;

    return sortedHead;
}

template <typename T>
SinglyLinkedList<T>::Node*
SinglyLinkedList<T>::findMiddle(Node* head) {
    if (!head) return nullptr;

    Node* slow = head;
    Node* fast = head->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}
