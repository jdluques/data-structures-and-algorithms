#include "linked_lists/singly.h"

#include <stdlib.h>

Node* node_new(void* value, Node* next) {
    Node* new_node = malloc(sizeof(Node));
    new_node->value_ = value;
    new_node->next_ = next;
    return new_node;
}


SinglyLinkedList* singly_list_new() {
    SinglyLinkedList* new_list = malloc(sizeof(SinglyLinkedList));

    Node* sentinel = node_new(NULL, NULL);

    new_list->sentinel_ = sentinel;
    new_list->tail_ = sentinel;
    new_list->size_ = 0;

    return new_list;
}

size_t size(SinglyLinkedList* list) {
    return list->size_;
}

bool is_empty(SinglyLinkedList* list) {
    return list->size_ == 0;
}

void* front(SinglyLinkedList* list) {
    return list->size_ > 0 ? list->sentinel_->next_->value_ : NULL;
}

void* back(SinglyLinkedList* list) {
    return list->size_ > 0 ? list->tail_->value_ : NULL;
}
    
void* at(SinglyLinkedList* list, size_t pos) {
    if (pos < 0 || pos >= list->size_) return NULL;

    if (pos == 0) return front(list);
    else if (pos == list->size_-1) return back(list);
    else {
        Node* curr = list->sentinel_;
        while (pos--) curr = curr->next_;
        return curr->value_;
    }
}

Node* search(SinglyLinkedList* list, void* value) {
    Node* curr = list->sentinel_->next_;
    while (curr) {
        if (curr->value_ == value) return curr;
    }
    return NULL;
}

void push_front(SinglyLinkedList* list, void* value) {
    Node* new_node = node_new(value, list->sentinel_->next_);
    list->sentinel_->next_ = new_node;

    if (list->size_ == 0) list->tail_ = new_node;

    list->size_++;
}

void push_back(SinglyLinkedList* list, void* value) {
    Node *new_node = node_new(value, NULL);
    
    if (list->tail_) list->tail_->next_ = new_node;
    else list->sentinel_->next_ = new_node;
    list->tail_ = new_node;

    list->size_++;
}

void insert(SinglyLinkedList* list, size_t pos, void* value) {
    if (pos < 0 || pos > list->size_) return;

    if (pos == 0) push_front(list, value);
    else if (pos == list->size_) push_back(list, value);
    else {
        Node* curr = list->sentinel_;
        while (pos--) curr = curr->next_;

        Node* new_node = node_new(value, curr->next_);
        curr->next_ = new_node;

        list->size_++;
    }
}

void* pop_front(SinglyLinkedList* list) {
    if (list->size_ == 0) return NULL;

    Node* prev_head = list->sentinel_->next_;
    void* prev_head_value = prev_head->value_;
    list->sentinel_->next_ = prev_head->next_;
    free(prev_head);
    if (list->size_ == 1) list->tail_ = list->sentinel_;

    list->size_--;

    return prev_head_value;
}

void* pop_back(SinglyLinkedList* list) {
    if (list->size_ == 0) return NULL;

    Node* curr = list->sentinel_;
    while (curr->next_ != list->tail_) curr = curr->next_;

    Node* prev_tail = list->tail_;
    void* prev_tail_value = prev_tail->value_;
    free(prev_tail);
    list->tail_ = curr;
    list->tail_->next_ = NULL;

    list->size_--;

    return prev_tail_value;
}

void* erase(SinglyLinkedList* list, size_t pos) {
    if (pos < 0 || pos > list->size_) return NULL;

    if (pos == 0) return pop_front(list);
    else if (pos == list->size_-1) return pop_back(list);
    else {
        Node* curr = list->sentinel_;
        while (curr--) curr = curr->next_;

        Node* node_to_delete = curr->next_;
        void* deleted_node_value = node_to_delete->value_;
        curr->next_ = node_to_delete->next_;
        free(node_to_delete);

        list->size_--;

        return deleted_node_value;
    }
}

void clear(SinglyLinkedList* list) {
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
    Node* dummy = node_new(NULL, NULL);
    Node* curr = dummy;

    while (head_1 && head_2) {
        if (head_1->value_ <= head_2->value_) {
            curr->next_ = head_1;
            head_1 = head_1->next_;
        } else {
            curr->next_ = head_2;
            head_2 = head_2->next_;
        }

        curr = curr->next_;
    }

    Node* sorted_head = dummy->next_;
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

void sort(SinglyLinkedList* list) {
    list->sentinel_ = sort_list(list->sentinel_->next_);
}

SinglyLinkedList* merge(SinglyLinkedList* list_1, SinglyLinkedList* list_2) {
    if (!is_empty(list_1) && is_empty(list_2)) return list_1;
    if (is_empty(list_1) && !is_empty(list_2)) return list_2;

    SinglyLinkedList* new_list = malloc(sizeof(SinglyLinkedList));
    new_list->sentinel_ = list_1->sentinel_;
    new_list->tail_ = list_2->tail_;
    new_list->size_ = list_1->size_ + list_2->size_;

    list_1->tail_->next_ = list_2->sentinel_->next_;
    free(list_2->sentinel_);

    return new_list;
}
