/** @file
 * Interfejs struktury stosu
 *
 * @author Szymon Michniak <s.michniak@student.uw.edu.pll>
 * @date 16.04.2020
 */

#ifndef GAMMA_STACK_H
#define GAMMA_STACK_H

#include "utilities.h"
#include <stdbool.h>
#include <stdio.h>

/**
 * Struktura przechowująca jeden element stosu.
 */
typedef struct stackNode StackNode_t;

/** @brief Tworzy stos
 * Alokuje pamięć na nowy stos. Inicjuje stos z wejściowymi wartościami.
 * @param[in] x  – numer kolumny, liczba nieujemna mniejsza od wartości
 *                      @p width z funkcji @ref gamma_new,
 * @param[in] y       – numer wiersza, liczba nieujemna mniejsza od wartości
 *                      @p height z funkcji @ref gamma_new.
 * @return Wskaźnik na pierwszy element utworzonego stosu lub NULL, jeśli nie udało sie zaalokować pamięci
 */
StackNode_t* createStack(uint32_t x, uint32_t y);

/** @brief Sprawdza, czy stos jest pusty.
 * @param[in] stackPtr  – wskaźnik na stos.
 * @return Wartość @p true, jeśli stos jest pusty lub @p false w przeciwnym przypadku.
 */
bool isStackEmpty(StackNode_t* stackPtr);

/** @brief Ustawia nowy element na koniec stosu.
 * Alokuje pamięć na nowy element stosu z wartościami @p x i @p y. Ustawia nowy element na koniec wejściowego
 * stosu.
 * @param[in, out] stackPtr  – wskaźnik na stos.
 * @param[in] x  – numer kolumny, liczba nieujemna mniejsza od wartości
 *                      @p width z funkcji @ref gamma_new,
 * @param[in] y       – numer wiersza, liczba nieujemna mniejsza od wartości
 *                      @p height z funkcji @ref gamma_new.
 * @return Wskaźnik na ostatni element stosu lub NULL, jeśli nie udało się zaalokować pamięci
 */
StackNode_t* putLast(StackNode_t* stackPtr, uint32_t x, uint32_t y);

/** @brief Usuwa ostatni element ze stosu.
 * Zwalania pamięć zajętą przez ostatni element. Zwraca nowy, ostatni element.
 * @param[in, out] stackPtr  – wskaźnik na stos.
 * @return Wskaźnik na nowy, ostatni element stosu po usunięciu.
 */
StackNode_t* removeLast(StackNode_t* stackPtr);

/** @brief Zwraca wartość ostatniego elementu ze stosu.
 * Tworzy i zwraca krotkę (@p x, @p y) z wartościami @p x i @p y z funkcji @ref createStack.
 * @param[in] stackPtr  – wskaźnik na stos.
 * @return Krotka @ref Tuple z wartościami z ostatniego elementu stosu.
 */
Tuple getLast(StackNode_t* stackPtr);

/** @brief Usuwa stos.
 * Zwalnia zaalokowaną pamięć na wszystkie elementy w stosie.
 * @param[in, out] stackPtr  – wskaźnik na stos.
 */
void removeStack(StackNode_t* stackPtr);

#endif //GAMMA_STACK_H
