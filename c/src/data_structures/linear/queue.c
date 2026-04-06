#include "data_structures/linear/queue.h"

#include <stdlib.h>

Queue* queue_new(size_t capacity) {
    Queue* queue = malloc(sizeof(Queue));

    queue->size_ = 0;
    queue->capacity_ = capacity;
    queue->head_ = 0;
    queue->tail_ = 0;
    queue->data_ = calloc(capacity, sizeof(void*));

    return queue;
}

void queue_destroy(Queue* queue, void (*free_func)(void*)) {
    for (size_t idx = queue->head_, i = 0; i < queue->size_; i++) {
        if (queue->data_[idx] && free_func) free_func(queue->data_[idx]);
        queue->data_[idx] = NULL;
        idx = (idx + 1) % queue->capacity_;
    }
    free(queue->data_);
    free(queue);
}

size_t size(Queue* queue) {
    return queue->size_;
}

bool is_empty(Queue* queue) {
    return queue->size_ == 0;
}

void* front(Queue* queue) {
    return queue->size_ != 0 ? queue->data_[queue->head_] : NULL;
}

void enqueue(Queue* queue, void* element) {
    if (((queue->tail_+1) % queue->capacity_) == queue->head_) {
        void** new_data = malloc(sizeof(void*) * (queue->capacity_*2));

        for (size_t i = 0, j = queue->head_;
                i < queue->size_;
                i++, j = (j+1) % queue->capacity_) {
            new_data[i] = queue->data_[j];
            queue->data_[j] = NULL;
        }

        free(queue->data_);
        queue->data_ = new_data;

        queue->head_ = 0;
        queue->tail_ = queue->size_-1;
        queue->capacity_ *= 2;
    }

    queue->tail_ = (queue->tail_ + 1) % queue->capacity_;
    queue->data_[queue->tail_] = element;
    queue->size_++;
}

void* pop(Queue* queue) {
    if (queue->size_ == 0) return NULL;

    void* prevFront = queue->data_[queue->head_];
    queue->data_[queue->head_] = NULL;

    queue->head_ = (queue->head_+1) % queue->capacity_;
    queue->size_--;

    return prevFront;
}

void clear(Queue* queue, void (*free_func)(void*)) {
    for (size_t idx = queue->head_, i = 0; i < queue->size_; i++) {
        if (queue->data_[idx] && free_func) free_func(queue->data_[idx]);
        queue->data_[idx] = NULL;
        idx = (idx + 1) % queue->capacity_;
    }
    queue->head_ = 0;
    queue->tail_ = 0;
    queue->size_ = 0;
}

void swap(Queue* a, Queue* b) {
    Queue temp = *a;
    *a = *b;
    *b = temp;
}
