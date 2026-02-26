#include "stack.h"

#include <stdlib.h>

Stack* stack_new(size_t capacity) {
    Stack* stack = malloc(sizeof(Stack));

    stack->size_ = 0;
    stack->capacity_ = capacity;
    stack->data_ = calloc(capacity, sizeof(void*));
    
    return stack;
}

void stack_destroy(Stack* stack) {
    for (size_t i = 0; i < stack->size_; i++) stack->data_[i] = NULL;
    free(stack->data_);
    free(stack);
}

size_t size(Stack* stack) {
    return stack->size_;
}

bool is_empty(Stack* stack) {
    return stack->size_ == 0;
}

void* peek(Stack* stack) {
    return stack->size_ != 0 ? stack->data_[stack->size_-1] : NULL;
}

void push(Stack* stack, void* element) {
    if (stack->size_ == stack->capacity_) {
        stack->capacity_ *= 2;
        
        void** new_data = malloc(sizeof(void*)*stack->capacity_);
        for (size_t i = 0; i < stack->size_; i++) new_data[i] = stack->data_[i];
        for (size_t i = stack->size_; i < stack->capacity_; i++) new_data[i] = NULL;

        free(stack->data_);
        stack->data_ = new_data;
    }

    stack->data_[stack->size_] = element;
    stack->size_++;
}

void* pop(Stack* stack) {
    if (stack->size_ == 0) return NULL;
    
    void* top_element = stack->data_[stack->size_-1];
    stack->data_[stack->size_-1] = NULL;
    stack->size_--;
    return top_element;
}

void clear(Stack* stack) {
    for (size_t i = 0; i < stack->size_; i++) {
        stack->data_[i] = NULL;
    }
}

void swap(Stack* a, Stack* b) {
    Stack temp = *a;
    *a = *b;
    *b = temp;
}
