/** @file
 * Interfejs struktury drzewa Find-Union
 *
 * @author Szymon Michniak <s.michniak@student.uw.edu.pl>
 * @date 16.04.2020
 */

#ifndef GAMMA_FINDUNION_H
#define GAMMA_FINDUNION_H

#include "stack.h"
#include <stdlib.h>

/** @struct findUnionNode_t
 * Struktura przechowująca wierzchołek drzewa Find-Union.
 */
typedef struct findUnionNode findUnionNode_t;

/** @brief Tworzy wierzchołek drzewa Find-Union.
 * Alokuje pamięć na nowy wierzchołek Find-Union. Inicjuje wierzchołek z wartością @p player.
 * @param[in] player  – numer gracza, liczba dodatnia niewiększa od wartości @p players z funkcji
 * @ref gamma_new,
 * @return Wskaźnik na utworzony wierzchołek lub NULL, gdy nie udało się zaalokować pamięci.
 */
findUnionNode_t* makeSet(uint32_t player);

/** @brief Zwraca gracza w danym wierzchołku.
 * Zwraca gracza w danym wierzchołku lub 0 dla pustego wierzchołka.
 * @param[in] nodePtr  – wskaźnik na wierzchołek drzewa lub NULL.
 * @return Wartość @p player z funkcji @ref makeSet lub @p 0, jeśli nodePtr jest NULL.
 */
uint32_t getPlayer(findUnionNode_t* nodePtr);

/** @brief Łączy dwa drzewa Find-Union.
 * Łączy dwa drzewa wykorzystując rangi drzew do optymalizacji. Drzewo z mniejszą rangą podczepiamy pod to, z
 * większą.
 * @param[in, out] nodePtr1  – wskaźnik na wierzchołek pierwszego drzewa,
 * @param[in, out] nodePtr2  – wskaźnik na wierzchołek drugiego drzewa.
 */
void unite(findUnionNode_t* nodePtr1, findUnionNode_t* nodePtr2);

/** @brief Sprawdza, czy dwa wierzchołki są w jednym drzewie.
 * Sprawdza, czy wierzchołki są w jednym drzewie wykorzystując strukturę Find-Union. Wierzchołki są połączone,
 * jeśli są w drzewie z tym samym korzeniem.
 * @param[in, out] nodePtr1  – wskaźnik na wierzchołek pierwszego drzewa,
 * @param[in, out] nodePtr2  – wskaźnik na wierzchołek drugiego drzewa.
 * @return Wartość @p true, jeśli są połączone, @p false jeśli dowolny z nich jest NULL lub nie są połączone.
 */
bool connected(findUnionNode_t* nodePtr1, findUnionNode_t* nodePtr2);


#endif //GAMMA_FINDUNION_H
