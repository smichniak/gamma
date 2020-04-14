#ifndef GAMMA_FINDUNION_H
#define GAMMA_FINDUNION_H

#include "stack.h"

typedef struct findUnionNode findUnionNode_t;

typedef struct findUnionNode {
    uint64_t player;
    //TODO
    //Think about this type size
    uint64_t depth;
    findUnionNode_t* parent;
} findUnionNode_t;


//TODO
//Change name to my style
findUnionNode_t* make_set(uint32_t player);

void merge(findUnionNode_t* a, findUnionNode_t* b);

bool connected(findUnionNode_t* a, findUnionNode_t* b);

#endif //GAMMA_FINDUNION_H
