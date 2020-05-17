/** @file
 * Implementacja modułu stack.h
 *
 * @author Szymon Michniak <s.michniak@student.uw.edu.pl>
 * @date 16.04.2020
 */

#include "stack.h"
#include <stdlib.h>

/** @struct stackNode
 * Struktura stosu. Przechowuje dwie wartości i wskaźnik na następny element stosu.
 */
struct stackNode {
    uint32_t x; ///< Pierwsza pamiętana wartość elementu stosu
    uint32_t y; ///< Druga pamiętana wartość elementu stosu
    stackNode_t* next; ///< Wskaźnik na nastepny element stosu
};

stackNode_t* createStack(uint32_t x, uint32_t y) {
    stackNode_t* node = malloc(sizeof(stackNode_t));
    if (!node) {
        return NULL;
    }
    node->next = NULL;
    node->x = x;
    node->y = y;
    return node;
}

inline bool isStackEmpty(stackNode_t* stackPtr) {
    return !stackPtr;
}

stackNode_t* putLast(stackNode_t* stackPtr, uint32_t x, uint32_t y) {
    stackNode_t* nodePtr = createStack(x, y);
    if (!nodePtr) {
        return NULL;
    }
    nodePtr->next = stackPtr;
    return nodePtr;
}

stackNode_t* removeLast(stackNode_t* stackPtr) {
    stackNode_t* toReturn = stackPtr->next;
    free(stackPtr);
    return toReturn;
}

inline Tuple getLast(stackNode_t* stackPtr) {
    return createTuple(stackPtr->x, stackPtr->y);
}

void removeStack(stackNode_t* stackPtr) {
    if (stackPtr) {
        removeStack(stackPtr->next);
        free(stackPtr);
    }
}





