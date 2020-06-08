/** @file
 * Implementacja modułu stack.h
 *
 * @author Szymon Michniak <s.michniak@student.uw.edu.pl>
 * @date 16.04.2020
 */

#include "stack.h"
#include <stdlib.h>

/** @struct stack_node
 * Struktura stosu. Przechowuje dwie wartości i wskaźnik na następny element stosu.
 */
struct stack_node {
    uint32_t x; ///< Pierwsza pamiętana wartość elementu stosu
    uint32_t y; ///< Druga pamiętana wartość elementu stosu
    stack_node_t* next; ///< Wskaźnik na nastepny element stosu
};

stack_node_t* create_stack(uint32_t x, uint32_t y) {
    stack_node_t* node = malloc(sizeof(stack_node_t));
    if (!node) {
        return NULL;
    }
    node->next = NULL;
    node->x = x;
    node->y = y;
    return node;
}

inline bool is_stack_empty(stack_node_t* stackPtr) {
    return !stackPtr;
}

stack_node_t* put_last(stack_node_t* stackPtr, uint32_t x, uint32_t y) {
    stack_node_t* nodePtr = create_stack(x, y);
    if (!nodePtr) {
        return NULL;
    }
    nodePtr->next = stackPtr;
    return nodePtr;
}

stack_node_t* remove_last(stack_node_t* stackPtr) {
    stack_node_t* toReturn = stackPtr->next;
    free(stackPtr);
    return toReturn;
}

inline tuple get_last(stack_node_t* stackPtr) {
    return create_tuple(stackPtr->x, stackPtr->y);
}

void remove_stack(stack_node_t* stackPtr) {
    if (stackPtr) {
        remove_stack(stackPtr->next);
        free(stackPtr);
    }
}





