#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

const int INITIAL_STACK_SIZE = 16;

struct stackNode {
    uint32_t x;
    uint32_t y;
    StackNode_t* next;
};

Tuple createTuple(uint32_t x, uint32_t y) {
    Tuple newTuple;
    newTuple.x = x;
    newTuple.y = y;
    return newTuple;
}

StackNode_t* createStack(uint32_t x, uint32_t y) {
    StackNode_t* node = malloc(sizeof(StackNode_t));
    if (!node) {
        return NULL;
    }
    node->next = NULL;
    node->x = x;
    node->y = y;
    return node;
}

bool isEmpty(StackNode_t* stackPtr) {
    return !stackPtr;
}

StackNode_t* putLast(StackNode_t* stackPtr, uint32_t x, uint32_t y) {
    StackNode_t* nodePtr = createStack(x, y);
    if (!nodePtr) {
        return NULL;
    }
    nodePtr->next = stackPtr;
    return nodePtr;
}

StackNode_t* removeLast(StackNode_t* stackPtr) {
    StackNode_t* toReturn = stackPtr->next;
    free(stackPtr);
    return toReturn;
}

Tuple getLast(StackNode_t* stackPtr) {
    return createTuple(stackPtr->x, stackPtr->y);
}

void removeStack(StackNode_t* stackPtr) {
    if (stackPtr) {
        removeStack(stackPtr->next);
        free(stackPtr);
    }
}





