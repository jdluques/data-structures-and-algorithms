#ifndef SINGLY_LIST_H
#define SINGLY_LIST_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    void* value_;
    struct Node* next_;
    struct Node* prev_;
} Node;

Node* node_new(void* value, Node* next, Node* prev_);


typedef struct DoublyLinkedList {
    Node* head_;
    Node* tail_;
    size_t size_;
} DoublyLinkedList;

DoublyLinkedList* doubly_list_new();

size_t size(DoublyLinkedList* list);
bool is_empty(DoublyLinkedList* list);

void* front(DoublyLinkedList* list);
void* back(DoublyLinkedList* list);
void* at(DoublyLinkedList* list, size_t pos);

Node* search(DoublyLinkedList* list, void* value);

void push_front(DoublyLinkedList* list, void* value);
void push_back(DoublyLinkedList* list, void* value);
void insert(DoublyLinkedList* list, size_t pos, void* value);

void* pop_front(DoublyLinkedList* list);
void* pop_back(DoublyLinkedList* list);
void* erase(DoublyLinkedList* list, size_t pos);

void clear(DoublyLinkedList* list);

void sort(DoublyLinkedList* list);
DoublyLinkedList* merge(DoublyLinkedList* list_1, DoublyLinkedList* list_2);

#endif
