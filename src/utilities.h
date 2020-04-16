#ifndef GAMMA_UTILITIES_H
#define GAMMA_UTILITIES_H

#include <stdint.h>

const uint32_t MAX_INT32;

typedef struct {
    uint32_t x;
    uint32_t y;
} Tuple;

Tuple createTuple(uint32_t x, uint32_t y);

int digits(uint32_t number);

#endif //GAMMA_UTILITIES_H
