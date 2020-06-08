/** @file
 * Interfejs funkcji pomocniczych
 *
 * @author Szymon Michniak <s.michniak@student.uw.edu.pl>
 * @date 16.04.2020
 */

#ifndef GAMMA_UTILITIES_H
#define GAMMA_UTILITIES_H

#include <stdint.h>

/** @struct tuple
 * Struktura pary uporządkowanej. Zawiera dwie liczby nieujemne.
 */
typedef struct {
    uint32_t x; ///< Pierwszy element pary
    uint32_t y; ///< Drugi element pary
} tuple;

/** @brief Tworzy nową parę.
 * Tworzy i zwraca parę z wejściowymi wartościami.
 * @param[in] x       – numer kolumny, liczba nieujemna mniejsza od wartości
 *                      @p width z funkcji @ref gamma_new,
 * @param[in] y       – numer wiersza, liczba nieujemna mniejsza od wartości
 *                      @p height z funkcji @ref gamma_new.
 * @return Para z wejściowymi wartościami
 */

tuple create_tuple(uint32_t x, uint32_t y);

/** @brief Zwraca liczbę cyfr liczby.
 * Zwraca liczbę cyfr liczby nieujemnej w zapisie dziesiętnym.
 * @param[in] number  – liczba nieujemna.
 * @return Liczba całkowita dodatnia, liczba cyfr liczby wejściowej,
 */
int digits(uint32_t number);

#endif /* GAMMA_UTILITIES_H */
