/** @file
 * Implementacja modułu findUnion.h
 *
 * @author Szymon Michniak <s.michniak@student.uw.edu.pl>
 * @date 16.04.2020
 */

#include "findUnion.h"

/** @struct find_union_node
 * Struktura umieszczana w zajętym polu, łączy się z sąsiednimi polami z tym samym graczem tworząc obszar.
 */
struct find_union_node {
    uint32_t player; ///< Numer gracza na polu
    uint64_t rank; ///< Ranga pola, używana w łączeniu drzew Find-Union
    find_union_node_t* parent; ///< Wskaźnik na rodziaca w strukturze Find-Union
};

find_union_node_t* make_set(uint32_t player) {
    find_union_node_t* nodePtr = malloc(sizeof(find_union_node_t));
    if (!nodePtr) {
        return NULL;
    }
    nodePtr->player = player;
    nodePtr->parent = nodePtr;
    nodePtr->rank = 0;
    return nodePtr;
}

inline uint32_t get_player(find_union_node_t* nodePtr) {
    if (!nodePtr) {
        return 0;
    }
    return nodePtr->player;
}

/** @brief Znajduje korzeń wejściowego drzewa.
 * Znajduje korzeń wejściowego drzewa Find-Union. Wykorzystuje kompresje ścieżek, by zmniejszać wysokość drzewa
 * i optymalizować kolejne wyszukania.
 * @param[in, out] nodePtr  – wskaźnik na wierzchołek drzewa.
 * @return Wskaźnik na korzeń drzewa, do którego należy wejściowy wierzchołek.
 */
static find_union_node_t* find(find_union_node_t* nodePtr) {
    if (nodePtr->parent != nodePtr) {
        // Kompresja ścieżek
        nodePtr->parent = find(nodePtr->parent);
    }
    return nodePtr->parent;
}

void unite(find_union_node_t* nodePtr1, find_union_node_t* nodePtr2) {
    find_union_node_t* nodePtrRoot1 = find(nodePtr1);
    find_union_node_t* nodePtrRoot2 = find(nodePtr2);

    if (nodePtrRoot1 != nodePtrRoot2) {
        if (nodePtrRoot1->rank < nodePtrRoot2->rank) {
            // Mniejsze drzewo podczepiamy pod większe, zapewnia dobrą złożoność
            nodePtrRoot1->parent = nodePtrRoot2;
            nodePtrRoot2->rank++;
        } else {
            nodePtrRoot2->parent = nodePtrRoot1;
            nodePtrRoot1->rank++;
        }
    }
}

inline bool connected(find_union_node_t* nodePtr1, find_union_node_t* nodePtr2) {
    return nodePtr1 && nodePtr2 && find(nodePtr1) == find(nodePtr2);
}
