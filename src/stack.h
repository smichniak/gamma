#ifndef GAMMA_STACK_H
#define GAMMA_STACK_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint32_t x;
    uint32_t y;
} Tuple;

typedef struct stackNode StackNode_t;

Tuple createTuple(uint32_t x, uint32_t y);

StackNode_t* createStack(uint32_t x, uint32_t y);

bool isEmpty(StackNode_t* stackPtr);

StackNode_t* putLast(StackNode_t* stackPtr, uint32_t x, uint32_t y);

StackNode_t* removeLast(StackNode_t* stackPtr);

Tuple getLast(StackNode_t* stackPtr);

void removeStack(StackNode_t* stackPtr);

#endif //GAMMA_STACK_H
