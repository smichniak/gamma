#ifndef GAMMA_STACK_H
#define GAMMA_STACK_H

#include "utilities.h"
#include <stdbool.h>
#include <stdio.h>

typedef struct stackNode StackNode_t;

StackNode_t* createStack(uint32_t x, uint32_t y);

bool isStackEmpty(StackNode_t* stackPtr);

StackNode_t* putLast(StackNode_t* stackPtr, uint32_t x, uint32_t y);

StackNode_t* removeLast(StackNode_t* stackPtr);

Tuple getLast(StackNode_t* stackPtr);

void removeStack(StackNode_t* stackPtr);

#endif //GAMMA_STACK_H
