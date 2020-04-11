#ifndef GAMMA_FINDUNION_H
#define GAMMA_FINDUNION_H

#include "stack.h"
#include "stdbool.h"

typedef struct findUnionNode {
    uint64_t player;
    //TODO
    //Think about this type size
    uint8_t depth;
    struct findUnionNode* parent;
} findUnionNode_t;

findUnionNode_t make_set();

void merge(findUnionNode_t* a, findUnionNode_t* b);

bool connected(findUnionNode_t* a, findUnionNode_t* b);

#endif //GAMMA_FINDUNION_H
