#ifndef GAMMA_DISPLAY_H
#define GAMMA_DISPLAY_H

#include "gamma.h"

char* boardWithHighlight(gamma_t* g, bool highlight, uint32_t x, uint32_t y);

void clear();

void printResults(gamma_t* g);


#endif //GAMMA_DISPLAY_H
