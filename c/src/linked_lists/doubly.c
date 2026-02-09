#include "linked_lists/doubly.h"

#include <stdlib.h>

Node* node_new(void* value, Node* next, Node* prev) {
    Node* new_node = malloc(sizeof(Node));
    new_node->value_ = value;
    new_node->next_ = next;
    new_node->prev_ = prev;
    return new_node;
}


DoublyLinkedList* doubly_list_new() {
    DoublyLinkedList* new_list = malloc(sizeof(DoublyLinkedList));

    Node* head_sentinel = node_new(NULL, NULL, NULL);
    Node* tail_sentinel = node_new(NULL, NULL, head_sentinel);
    head_sentinel->next_ = tail_sentinel;

    new_list->head_ = head_sentinel;
    new_list->tail_ = tail_sentinel;
    new_list->size_ = 0;

    return new_list;
}

size_t size(DoublyLinkedList* list) {
    return list->size_;
}

bool is_empty(DoublyLinkedList* list) {
    return list->size_ == 0;
}

void* front(DoublyLinkedList* list) {
    return list->size_ > 0 ? list->head_->next_->value_ : NULL;
}

void* back(DoublyLinkedList* list) {
    return list->size_ > 0 ? list->tail_->prev_->value_ : NULL;
}
    
void* at(DoublyLinkedList* list, size_t pos) {
    if (pos < 0 || pos >= list->size_) return NULL;

    if (pos == 0) return front(list);
    else if (pos == list->size_-1) return back(list);
    else {
        Node* curr;
        if (pos < list->size_/2) {
            curr = list->head_->next_;
            while (pos--) curr = curr->next_;
        } else {
            pos = list->size_ - pos;
            curr = list->tail_;
            while (pos--) curr = curr->prev_;
        }
        return curr->value_;
    }
}

Node* search(DoublyLinkedList* list, void* value) {
    Node* curr = list->head_->next_;
    while (curr != list->tail_) {
        if (curr->value_ == value) return curr;
    }
    return NULL;
}

void push_front(DoublyLinkedList* list, void* value) {
    Node* new_node = node_new(value, list->head_->next_, list->head_);
    list->head_->next_ = new_node;

    if (list->size_ == 0) list->tail_->prev_ = new_node;

    list->size_++;
}

void push_back(DoublyLinkedList* list, void* value) {
    Node *new_node = node_new(value, list->tail_, list->tail_->prev_); 
    list->tail_->prev_ = new_node;

    if (list->size_ == 0) list->head_->next_ = new_node;

    list->size_++;
}

void insert(DoublyLinkedList* list, size_t pos, void* value) {
    if (pos < 0 || pos > list->size_) return;

    if (pos == 0) push_front(list, value);
    else if (pos == list->size_) push_back(list, value);
    else {
        Node* curr;
        if (pos < list->size_/2) {
            curr = list->head_;
            while (pos--) curr = curr->next_;
        } else {
            pos = list->size_ - pos;
            curr = list->tail_->prev_;
            while (pos--) curr = curr->prev_;
        }

        Node* new_node = node_new(value, curr->next_, curr);
        curr->next_ = new_node;
        new_node->next_->prev_ = new_node;

        list->size_++;
    }
}

void* pop_front(DoublyLinkedList* list) {
    if (list->size_ == 0) return NULL;

    Node* prev_head = list->head_->next_;
    void* prev_head_value = prev_head->value_;
    list->head_->next_ = prev_head->next_;
    prev_head->next_->prev_ = list->head_;
    free(prev_head);

    list->size_--;

    return prev_head_value;
}

void* pop_back(DoublyLinkedList* list) {
    if (list->size_ == 0) return NULL;

    Node* prev_tail = list->tail_->prev_;
    void* prev_tail_value = prev_tail->value_;
    list->tail_->prev_ = prev_tail->prev_;
    prev_tail->prev_->next_ = list->tail_;
    free(prev_tail);

    list->size_--;

    return prev_tail_value;
}

void* erase(DoublyLinkedList* list, size_t pos) {
    if (pos < 0 || pos >= list->size_) return NULL;

    if (pos == 0) return pop_front(list);
    else if (pos == list->size_-1) return pop_back(list);
    else {
        Node* curr;
        if (pos < list->size_/2) {
            curr = list->head_->next_;
            while (pos--) curr = curr->next_;
        } else {
            pos = list->size_ - pos;
            curr = list->tail_;
            while (pos--) curr = curr->prev_;
        }

        curr->prev_->next_ = curr->next_;
        curr->next_->prev_ = curr->prev_;

        void* deleted_node_value = curr->value_;

        free(curr);
        list->size_--;
        
        return deleted_node_value;
    }
}

void clear(DoublyLinkedList* list) {
    while (list->size_ != 0) pop_front(list);
}

Node* find_middle(Node* head) {
    if (!head) return NULL;

    Node* slow = head;
    Node* fast = head->next_;

    while (fast && fast->next_) {
        slow = slow->next_;
        fast = fast->next_->next_;
    }

    return slow;
}

Node* merge_helper(Node* head_1, Node* head_2) {
    Node* dummy = node_new(NULL, NULL, NULL);
    Node* curr = dummy;

    while (head_1 && head_2) {
        if (head_1->value_ <= head_2->value_) {
            curr->next_ = head_1;
            head_1->prev_ = curr;
            head_1 = head_1->next_;
        } else {
            curr->next_ = head_2;
            head_2->prev_ = curr;
            head_2 = head_2->next_;
        }

        curr = curr->next_;
    }

    Node* sorted_head = dummy->next_;
    dummy->next_->prev_ = NULL;
    free(dummy);

    return sorted_head;
}

Node* sort_list(Node* head) {
    if (!head || !head->next_) return head;

    Node* middle = find_middle(head);
    Node* rigth_head = middle->next_;
    middle->next_ = NULL;

    Node* sorted_left_head = sort_list(head);
    Node* sorted_right_head = sort_list(rigth_head);

    return merge_helper(sorted_left_head, sorted_right_head);
}

void sort(DoublyLinkedList* list) {
    list->tail_->prev_->next_ = NULL;

    list->head_ = sort_list(list->head_->next_);

    Node* curr = list->head_;
    while (curr && curr->next_) curr = curr->next_;
    curr->next_ = list->tail_;
    list->tail_->prev_ = curr;
}

DoublyLinkedList* merge(DoublyLinkedList* list_1, DoublyLinkedList* list_2) {
    if (!is_empty(list_1) && is_empty(list_2)) return list_1;
    if (is_empty(list_1) && !is_empty(list_2)) return list_2;

    DoublyLinkedList* new_list = malloc(sizeof(DoublyLinkedList));
    new_list->head_ = list_1->head_;
    new_list->tail_ = list_2->tail_;
    new_list->size_ = list_1->size_ + list_2->size_;

    list_1->tail_->prev_->next_ = list_2->head_->next_;
    list_2->head_->next_->prev_ = list_1->tail_->prev_;
    free(list_1->tail_);
    free(list_2->head_);

    return new_list;
}
