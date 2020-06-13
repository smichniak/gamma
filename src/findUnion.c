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
    find_union_node_t* node_ptr = malloc(sizeof(find_union_node_t));
    if (!node_ptr) {
        return NULL;
    }
    node_ptr->player = player;
    node_ptr->parent = node_ptr;
    node_ptr->rank = 0;
    return node_ptr;
}

inline uint32_t get_player(find_union_node_t* node_ptr) {
    if (!node_ptr) {
        return 0;
    }
    return node_ptr->player;
}

/** @brief Znajduje korzeń wejściowego drzewa.
 * Znajduje korzeń wejściowego drzewa Find-Union. Wykorzystuje kompresje ścieżek, by zmniejszać wysokość drzewa
 * i optymalizować kolejne wyszukania.
 * @param[in, out] node_ptr  – wskaźnik na wierzchołek drzewa.
 * @return Wskaźnik na korzeń drzewa, do którego należy wejściowy wierzchołek.
 */
static find_union_node_t* find(find_union_node_t* node_ptr) {
    if (node_ptr->parent != node_ptr) {
        // Kompresja ścieżek
        node_ptr->parent = find(node_ptr->parent);
    }
    return node_ptr->parent;
}

void unite(find_union_node_t* node_ptr1, find_union_node_t* node_ptr2) {
    find_union_node_t* node_ptr_root1 = find(node_ptr1);
    find_union_node_t* node_ptr_root2 = find(node_ptr2);

    if (node_ptr_root1 != node_ptr_root2) {
        if (node_ptr_root1->rank < node_ptr_root2->rank) {
            // Mniejsze drzewo podczepiamy pod większe, zapewnia dobrą złożoność
            node_ptr_root1->parent = node_ptr_root2;
            node_ptr_root2->rank++;
        } else {
            node_ptr_root2->parent = node_ptr_root1;
            node_ptr_root1->rank++;
        }
    }
}

inline bool connected(find_union_node_t* node_ptr1, find_union_node_t* node_ptr2) {
    return node_ptr1 && node_ptr2 && find(node_ptr1) == find(node_ptr2);
}
