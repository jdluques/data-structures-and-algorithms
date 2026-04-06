#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>

typedef struct Queue {
    size_t size_;
    size_t capacity_;
    size_t head_;
    size_t tail_;
    void** data_;
} Queue;

Queue* queue_new(size_t capacity);
void queue_destroy(Queue* queue, void (*free_func)(void*));

size_t size(Queue* queue);
bool is_empty(Queue* queue);

void* front(Queue* queue);

void enqueue(Queue* queue, void* element);

void* pop(Queue* queue);
void clear(Queue* queue, void (*free_func)(void*));

void swap(Queue* a, Queue* b);

#endif
