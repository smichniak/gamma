#ifndef GAMMA_FINDUNION_H
#define GAMMA_FINDUNION_H

#include "stack.h"
#include <stdlib.h>

typedef struct findUnionNode findUnionNode_t;

typedef struct findUnionNode {
    uint32_t player;
    uint64_t rank;
    findUnionNode_t* parent;
} findUnionNode_t;

findUnionNode_t* makeSet(uint32_t player);

void unite(findUnionNode_t* nodePtr1, findUnionNode_t* nodePtr2);

bool connected(findUnionNode_t* a, findUnionNode_t* b);

bool isRoot(findUnionNode_t* a);

#endif //GAMMA_FINDUNION_H
