/** @file
 * Interfejs funkcji pomocniczych
 *
 * @author Szymon Michniak <s.michniak@student.uw.edu.pll>
 * @date 16.04.2020
 */

#ifndef GAMMA_UTILITIES_H
#define GAMMA_UTILITIES_H

#include <stdint.h>

/** @brief Maksymalan wartość zmiennej typu uint32_t.
 */
const uint32_t MAX_INT32;


typedef struct {
    uint32_t x;
    uint32_t y;
} Tuple;

Tuple createTuple(uint32_t x, uint32_t y);

int digits(uint32_t number);

#endif //GAMMA_UTILITIES_H
