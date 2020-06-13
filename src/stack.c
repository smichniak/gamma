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

inline bool is_stack_empty(stack_node_t* stack_ptr) {
    return !stack_ptr;
}

stack_node_t* put_last(stack_node_t* stack_ptr, uint32_t x, uint32_t y) {
    stack_node_t* node_ptr = create_stack(x, y);
    if (!node_ptr) {
        return NULL;
    }
    node_ptr->next = stack_ptr;
    return node_ptr;
}

stack_node_t* remove_last(stack_node_t* stack_ptr) {
    stack_node_t* to_return = stack_ptr->next;
    free(stack_ptr);
    return to_return;
}

inline tuple get_last(stack_node_t* stack_ptr) {
    return create_tuple(stack_ptr->x, stack_ptr->y);
}

void remove_stack(stack_node_t* stack_ptr) {
    if (stack_ptr) {
        remove_stack(stack_ptr->next);
        free(stack_ptr);
    }
}





