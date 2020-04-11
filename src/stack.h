#ifndef GAMMA_STACK_H
#define GAMMA_STACK_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint32_t x;
    uint32_t y;
} Tuple;

typedef struct stack Stack_t;

Tuple createTuple(uint32_t x, uint32_t y);

Stack_t createStack_t();

bool isEmpty(Stack_t* stackPtr);

void putLast(Stack_t* stackPtr, Tuple element);

Tuple removeLast(Stack_t* stackPtr);

void removeStack_t(Stack_t* stackPtr);

#endif //GAMMA_STACK_H
