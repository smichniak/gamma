#include "findUnion.h"
#include <stdlib.h>

findUnionNode_t* make_set(uint32_t player) {
    findUnionNode_t* nodePtr = malloc(sizeof(findUnionNode_t));
    if (!nodePtr) {
        return NULL;
    }
    nodePtr->player = player;
    nodePtr->parent = nodePtr;
    nodePtr->depth = 1;
    return nodePtr;
}

findUnionNode_t* find(findUnionNode_t* element) {
    //TODO
    //necessary?
    // if (!element) return NULL;
    while (element->parent != element) {
        element->parent = element->parent->parent;
        element = element->parent;
    }
    return element;
}

void merge(findUnionNode_t* a, findUnionNode_t* b) {
    findUnionNode_t* root_a = find(a);
    findUnionNode_t* root_b = find(b);
    if (root_a != root_b) {
        if (root_a->depth > root_b->depth) { //merge by rank
            root_b->parent = root_a;
            root_a->depth++;
        } else {
            root_a->parent = root_b;
            root_b->depth++;
        }
    }
}

bool connected(findUnionNode_t* a, findUnionNode_t* b) {
    return a && b && find(a) == find(b);
}
