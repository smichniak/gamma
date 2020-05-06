#ifndef GAMMA_INPUTPARSER_H
#define GAMMA_INPUTPARSER_H

#include <stdbool.h>
#include <stdint.h>

typedef struct{
    char function;
    uint32_t firstArgument;
    uint32_t secondArgument;
    uint32_t thirdArgument;
    uint32_t fourthArgument;
    bool isValid;

} command_t;

command_t getCommand(char* line);

#endif //GAMMA_INPUTPARSER_H
