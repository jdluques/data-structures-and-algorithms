#ifndef SINGLY_LIST_H
#define SINGLY_LIST_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    void* value_;
    struct Node* next_;
} Node;

Node* node_new(void* value, Node* next);


typedef struct SinglyLinkedList {
    Node* sentinel_;
    Node* tail_;
    size_t size_;
} SinglyLinkedList;

SinglyLinkedList* singly_list_new();

size_t size(SinglyLinkedList* list);
bool is_empty(SinglyLinkedList* list);

void* front(SinglyLinkedList* list);
void* back(SinglyLinkedList* list);
void* at(SinglyLinkedList* list, size_t pos);

Node* search(SinglyLinkedList* list, void* value);

void push_front(SinglyLinkedList* list, void* value);
void push_back(SinglyLinkedList* list, void* value);
void insert(SinglyLinkedList* list, size_t pos, void* value);

void* pop_front(SinglyLinkedList* list);
void* pop_back(SinglyLinkedList* list);
void* erase(SinglyLinkedList* list, size_t pos);

void clear(SinglyLinkedList* list);

void sort(SinglyLinkedList* list);
SinglyLinkedList* merge(SinglyLinkedList* list_1, SinglyLinkedList* list_2);

#endif
