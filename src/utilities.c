#include "utilities.h"

const uint32_t MAX_INT32 = 4294967295;

Tuple createTuple(uint32_t x, uint32_t y) {
    Tuple newTuple;
    newTuple.x = x;
    newTuple.y = y;
    return newTuple;
}

int digits(uint32_t number) {
    if (number < 10) {
        return 1;
    } else {
        return 1 + digits(number / 10);
    }
}
