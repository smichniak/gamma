#ifndef GAMMA_STACK_H
#define GAMMA_STACK_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    int x;
    int y;
} Tuple;

typedef struct stack Stack;

Tuple createTuple(uint32_t x, uint32_t y);

Stack createStack();

bool isEmpty(Stack* stackPtr);

void putLast(Stack* stackPtr, Tuple element);

Tuple removeLast(Stack* stackPtr);

void removeStack(Stack* stackPtr);

#endif //GAMMA_STACK_H
