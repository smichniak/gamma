/** @file
 * Implementacja modułu utilities.h
 *
 * @author Szymon Michniak <s.michniak@student.uw.edu.pl>
 * @date 16.04.2020
 */

#include "utilities.h"

Tuple createTuple(uint32_t x, uint32_t y) {
    Tuple newTuple;
    newTuple.x = x;
    newTuple.y = y;
    return newTuple;
}

int digits(uint32_t number) {
    int digitCount = 0;
    do {
        digitCount++;
        number /= 10;
    } while (number != 0);
    return digitCount;
}
