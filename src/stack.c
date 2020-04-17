/** @file
 * Implementacja modułu stack.h
 *
 * @author Szymon Michniak <s.michniak@student.uw.edu.pll>
 * @date 16.04.2020
 */

#include "stack.h"
#include <stdlib.h>

/** @struct stackNode Struktura stosu.
 */
struct stackNode {
    uint32_t x; ///< Pierwsza pamiętana wartość elementu stosu
    uint32_t y; ///< Druga pamiętana wartość elementu stosu
    StackNode_t* next; ///< Wskaźnik na nastepny element stosu
};

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

bool isStackEmpty(StackNode_t* stackPtr) {
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





