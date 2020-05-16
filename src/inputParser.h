/** @file
 * Interfejs modułu, który odpowiada za interpretację wejścia programu.
 *
 * @author Szymon Michniak <s.michniak@student.uw.edu.pl>
 * @date 16.05.2020
 */

#ifndef GAMMA_INPUTPARSER_H
#define GAMMA_INPUTPARSER_H

#include "gamma.h"

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

void executeCommand(command_t command, gamma_t** g, unsigned long long line);


#endif //GAMMA_INPUTPARSER_H
