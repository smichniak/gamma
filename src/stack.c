#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

const int INITIAL_STACK_SIZE = 16;

struct stack {
    Tuple* stackArray;
    uint64_t lastIndex;
    uint64_t size;
};

Tuple createTuple(uint32_t x, uint32_t y) {
    Tuple newTuple;
    newTuple.x = x;
    newTuple.y = y;
    return newTuple;
}

Stack createStack() {
    Stack newStack;
    Tuple* stackArray = NULL;
    stackArray = (Tuple*) malloc(sizeof(Tuple) * INITIAL_STACK_SIZE);
    if (stackArray == NULL) {
        exit(1);
    }

    newStack.stackArray = stackArray;
    newStack.size = INITIAL_STACK_SIZE;
    newStack.lastIndex = 0;
    return newStack;
}

bool isEmpty(Stack* stackPtr) {
    return stackPtr->lastIndex == 0;
}

void putLast(Stack* stackPtr, Tuple element) {
    if (stackPtr->lastIndex + 1 == stackPtr->size) {
        stackPtr->stackArray = realloc(stackPtr->stackArray, 2 * stackPtr->size * sizeof(Tuple));
        if (stackPtr->stackArray == NULL) {
            exit(1);
        }
    }
    stackPtr->lastIndex++;
    stackPtr->stackArray[stackPtr->lastIndex] = element;
}

Tuple removeLast(Stack* stackPtr) {
    Tuple last = stackPtr->stackArray[stackPtr->lastIndex];
    stackPtr->lastIndex--;
    if (stackPtr->lastIndex <= stackPtr->size / 4 && stackPtr->size / 2 >= INITIAL_STACK_SIZE) {
        stackPtr->stackArray = realloc(stackPtr->stackArray, stackPtr->size * sizeof(Tuple) / 2);
        if (stackPtr->stackArray == NULL) {
            exit(1);
        }
    }
    return last;
}

void removeStack(Stack* stackPtr) {
    free(stackPtr->stackArray);
}




