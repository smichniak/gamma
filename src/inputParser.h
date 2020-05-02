#ifndef GAMMA_INPUTPARSER_H
#define GAMMA_INPUTPARSER_H

#include <stdbool.h>

typedef struct {
    char *function;
    char *firstArgument;
    char *secondArgument;
    char *thirdArgument;
    bool isValid;

} Command;

Command getCommand(char *line);

#endif //GAMMA_INPUTPARSER_H
