/** @file
 * Implementacja modułu utilities.h
 *
 * @author Szymon Michniak <s.michniak@student.uw.edu.pl>
 * @date 16.04.2020
 */

#include "utilities.h"

tuple create_tuple(uint32_t x, uint32_t y) {
    tuple new_tuple;
    new_tuple.x = x;
    new_tuple.y = y;
    return new_tuple;
}

int digits(uint32_t number) {
    int digit_count = 0;
    do {
        digit_count++;
        number /= 10;
    } while (number != 0);
    return digit_count;
}


bool only_digits(char* string) {
    for (uint32_t i = 0; i < strlen(string); ++i) {
        if (!isdigit(string[i])) {
            return false;
        }
    }
    return true;
}
