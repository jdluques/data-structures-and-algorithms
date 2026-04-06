#ifndef STACK_H
#define STACK_H

#include <stddef.h>

typedef struct Stack {
    size_t size_;
    size_t capacity_;
    void** data_;
} Stack;

Stack* stack_new(size_t capacity);
void stack_destroy(Stack* stack);

size_t size(Stack* stack);
bool is_empty(Stack* stack);

void* peek(Stack* stack);

void push(Stack* stack, void* element);

void* pop(Stack* stack);
void clear(Stack* stack);

void swap(Stack* a, Stack* b);

#endif
