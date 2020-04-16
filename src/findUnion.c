/** @file
 * Implementacja modułu findUnion.h
 *
 * @author Szymon Michniak <s.michniak@student.uw.edu.pll>
 * @date 16.04.2020
 */

#include "findUnion.h"

findUnionNode_t* makeSet(uint32_t player) {
    findUnionNode_t* nodePtr = malloc(sizeof(findUnionNode_t));
    if (!nodePtr) {
        return NULL;
    }
    nodePtr->player = player;
    nodePtr->parent = nodePtr;
    nodePtr->rank = 0;
    return nodePtr;
}

findUnionNode_t* find(findUnionNode_t* element) {
    if (element->parent != element) {
        element->parent = find(element->parent);
    }
    return element->parent;
}

void unite(findUnionNode_t* nodePtr1, findUnionNode_t* nodePtr2) {
    findUnionNode_t* nodePtrRoot1 = find(nodePtr1);
    findUnionNode_t* nodePtrRoot2 = find(nodePtr2);

    if (nodePtrRoot1 != nodePtrRoot2) {
        if (nodePtrRoot1->rank < nodePtrRoot2->rank) {
            nodePtrRoot1->parent = nodePtrRoot2;
            nodePtrRoot2->rank++;
        } else {
            nodePtrRoot2->parent = nodePtrRoot1;
            nodePtrRoot1->rank++;
        }
    }
}

bool connected(findUnionNode_t* NodePtr1, findUnionNode_t* NodePtr2) {
    return NodePtr1 && NodePtr2 && find(NodePtr1) == find(NodePtr2);
}
