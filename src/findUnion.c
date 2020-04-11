#include "findUnion.h"
#include <stdlib.h>

findUnionNode_t make_set(uint32_t player) {
    findUnionNode_t node;
    node.player = player;
    node.parent = NULL;
    node.depth = 1;
    return node;
}

findUnionNode_t* find(findUnionNode_t* element) {
    if (!element) return NULL;
    findUnionNode_t* original_element = element;
    while (element->parent != NULL)
        element = element->parent;
    if (element != original_element->parent && element != original_element)
        original_element->parent = element; //path compression
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
    return find(a) == find(b);
}
