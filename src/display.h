#ifndef GAMMA_DISPLAY_H
#define GAMMA_DISPLAY_H

#include "gamma.h"
#include <unistd.h>
#include <termios.h>

char* boardWithHighlight(gamma_t* g, uint32_t x, uint32_t y);

void clear();

struct termios changeTerminalToRaw();

void changeTerminalToOriginal(struct termios original);

void printResults(gamma_t* g);

void printError(unsigned long line);


#endif //GAMMA_DISPLAY_H
