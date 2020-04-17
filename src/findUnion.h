/** @file
 * Interfejs struktury drzewa Find-Union
 *
 * @author Szymon Michniak <s.michniak@student.uw.edu.pll>
 * @date 16.04.2020
 */

#ifndef GAMMA_FINDUNION_H
#define GAMMA_FINDUNION_H

#include "stack.h"
#include <stdlib.h>

typedef struct findUnionNode findUnionNode_t;

/** @struct findUnionNode Struktura umieszczana w zajętym polu, łączy się z sąsiednimi z tym samym
 * graczem polami tworząc obszar.
 */
typedef struct findUnionNode {
    uint32_t player; ///< Numer gracza na polu
    uint64_t rank; ///< Ranga pola, używana w łączeniu drzew Find-Union
    findUnionNode_t* parent; ///< Wskaźnik na rodziaca w strukturze Find-Union
} findUnionNode_t;

/** @brief Tworzy wierzchołek drzewa Find-Union.
 * Alokuje pamięć na nowy wierzchołek Find-Union. Inicjuje wierzchołek z wejściowym graczem.
 * @param[in] player  – numer gracza, liczba dodatnia niewiększa od wartości @p players z funkcji
 * @ref gamma_new,
 * @return Wskaźnik na utworzony wierzchołek lub NULL, gdy nie udało się zaalokować pamięci.
 */
findUnionNode_t* makeSet(uint32_t player);

/** @brief Łączy dwa drzewa Find-Union.
 * Łączy dwa drzewa wykorzystując rangi drzew do optymalizacji. Drzewo z mniejszą rangą podczepiamy pod to, z
 * większą.
 * @param[in, out] nodePtr1  – wskaźnik na wierzchołek pierwszego drzewa
 * @param[in, out] nodePtr2  – wskaźnik na wierzchołek drugiego drzewa
 */
void unite(findUnionNode_t* nodePtr1, findUnionNode_t* nodePtr2);

/** @brief Sprawdza, czy dwa wierzchołki są w jednym drzewie.
 * Sprawdza, czy wierzchołki są w jednym drzewie wykorzystując strukturę Find-Union. Wierzchołki są połączone,
 * jeśli są w drzewie z tym samym korzeniem.
 * @param[in, out] nodePtr1  – wskaźnik na wierzchołek pierwszego drzewa
 * @param[in, out] nodePtr2  – wskaźnik na wierzchołek drugiego drzewa
 * @return true, jeśli są połączone, false jeśli dowolny z nich jest NULL lub nie są połączone
 */
bool connected(findUnionNode_t* NodePtr1, findUnionNode_t* NodePtr2);


#endif //GAMMA_FINDUNION_H
