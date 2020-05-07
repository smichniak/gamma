#ifndef GAMMA_INPUTPARSER_H
#define GAMMA_INPUTPARSER_H

#include "gamma.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint32_t value;
    bool valid;
    bool empty;
} argument_t;


typedef struct {
    char function;
    argument_t firstArgument;
    argument_t secondArgument;
    argument_t thirdArgument;
    argument_t fourthArgument;
    bool isValid;
} command_t;

command_t getCommand(char* line);

gamma_t* executeCommand(command_t command, gamma_t* g, int line);

#endif //GAMMA_INPUTPARSER_H
