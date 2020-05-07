#define _XOPEN_SOURCE 700

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include "gamma.h"
#include "inputParser.h"

size_t INITIAL_BUFFER_SIZE = 0;

int main() {
    char* line = NULL;
    gamma_t* g = NULL;
    int lineNum = 1;

    while (getline(&line, &INITIAL_BUFFER_SIZE, stdin) > 0) {
        command_t command = getCommand(line);
        g = executeCommand(command, g, lineNum);
        lineNum++;
        free(line);
        line = NULL;
    }
    free(line);

    return 0;


}