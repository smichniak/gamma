#include "inputParser.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

//Whitespace characters that separate command arguments
const char WHITE_CHARS[] = " \t\v\f\r";
const char* VALID_FUNCTIONS = "BImgbfqp ";

//Default command is valid and does nothing
command_t defaultCommand() {
    command_t defComamand;
    return defComamand;
}

bool isWhite(char character) {
    for (uint32_t i = 0; i < strlen(WHITE_CHARS); ++i) {
        if (WHITE_CHARS[i] == character) {
            return true;
        }
    }
    return false;
}

/*bool isZero(char* string) {
    if (strlen(string) < 1) {
        return false;
    }
    for (uint32_t i = 0; i < strlen(string); ++i) {
        if (string[i] != '0') {
            return false;
        }
    }
    return true;
}*/

bool onlyDigits(char* string) {
    for (uint32_t i = 0; i < strlen(string); ++i) {
        if (!isdigit(string[i])) {
            return false;
        }
    }
    return true;
}


bool validFunction(char* function) {
    if (strlen(function) > 1) {
        return false;
    }

    for (uint32_t i = 0; i < strlen(VALID_FUNCTIONS); ++i) {
        if (VALID_FUNCTIONS[i] == function[0]) {
            return true;
        }
    }
    return false;
}

argument_t validArgument(char* string) {
    argument_t argument;
    argument.value = 0;
    argument.valid = true;
    argument.empty = false;

    if (string == NULL) {
        argument.empty = true;
    } else if (!onlyDigits(string)) {
        argument.valid = false;
    } else {
        uint64_t conversion = strtoul(string, NULL, 10);
       if (conversion > UINT32_MAX) {
           argument.valid = false;
       } else {
            argument.value = conversion;
       }

    }

    return argument;
}


command_t getCommand(char* line) {
    command_t command;
    command.function = ' ';
    command.isValid = true;

    if (line != NULL && line[0] != '#' && line[0] != '\n') {
        if (isWhite(line[0])) {
            command.isValid = false;
        } else if (line[strlen(line) - 1] != '\n') {
            char* noWhites = strtok(line, WHITE_CHARS);
            if (noWhites != NULL) { //Line with only white characters and no \n is valid
                command.isValid = false;
            }
        } else {
            //We remove the \n from the end of the line
            line[strlen(line) - 1] = 0;

            //We get every part separated by white characters
            char* function = strtok(line, WHITE_CHARS);

            char* firstArg = strtok(NULL, WHITE_CHARS);
            argument_t firstArgument = validArgument(firstArg);

            char* secondArg = strtok(NULL, WHITE_CHARS);
            argument_t secondArgument = validArgument(secondArg);

            char* thirdArg = strtok(NULL, WHITE_CHARS);
            argument_t thirdArgument = validArgument(thirdArg);

            char* fourthArg = strtok(NULL, WHITE_CHARS);
            argument_t fourthArgument = validArgument(fourthArg);

            char* restOfLine = strtok(NULL, WHITE_CHARS);

            if (function != NULL) {
                if (restOfLine != NULL || !validFunction(function) || !firstArgument.valid ||
                    !secondArgument.valid || !thirdArgument.valid ||
                    !fourthArgument.valid) {
                    //Valid line can't have more thant four arguments and each argument must be valid
                    command.isValid = false;
                } else {
                    command.function = function[0];
                    command.firstArgument = firstArgument;
                    command.secondArgument = secondArgument;
                    command.thirdArgument = thirdArgument;
                    command.fourthArgument = fourthArgument;
                }
            }
        }
    }
    return command;
}


gamma_t* executeCommand(command_t command, gamma_t* g, int line) {
    if (!command.isValid) {
        fprintf(stderr, "ERROR %d\n", line);
    } else {
        switch (command.function) {
            case 'B':
                if (g) {
                    fprintf(stderr, "ERROR %d\n", line);
                } else {
                    gamma_t* result = gamma_new(command.firstArgument.value, command.secondArgument.value,
                                                command.thirdArgument.value, command.fourthArgument.value);
                    if (!result) {
                        fprintf(stderr, "ERROR %d\n", line);
                    } else {
                        g = result;
                        printf("OK %d\n", line);
                    }
                }
                break;
            case 'I':
                fprintf(stderr, "ERROR %d\n", line);
                break;
            case 'p':
                if (!command.firstArgument.empty) {
                    fprintf(stderr, "ERROR %d\n", line);
                } else {
                    char* board = gamma_board(g);
                    if (!board) {
                        fprintf(stderr, "ERROR %d\n", line);
                    } else {
                        printf("%s", board);
                    }
                }
                break;
            case 'q':
                if (command.firstArgument.empty || !command.secondArgument.empty) {
                    fprintf(stderr, "ERROR %d\n", line);
                } else {
                    printf("%d\n", gamma_golden_possible(g, command.firstArgument.value));
                }
                break;
            case 'f':
                if (command.firstArgument.empty || !command.secondArgument.empty) {
                    fprintf(stderr, "ERROR %d\n", line);
                } else {
                    printf("%llu\n", gamma_free_fields(g, command.firstArgument.value));
                }
                break;
            case 'b':
                if (command.firstArgument.empty || !command.secondArgument.empty) {
                    fprintf(stderr, "ERROR %d\n", line);
                } else {
                    printf("%llu\n", gamma_busy_fields(g, command.firstArgument.value));
                }
                break;
            case 'g':
                if (command.thirdArgument.empty || !command.fourthArgument.empty) {
                    fprintf(stderr, "ERROR %d\n", line);
                } else {
                    printf("%d\n",
                           gamma_golden_move(g, command.firstArgument.value, command.secondArgument.value,
                                             command.thirdArgument.value));
                }
                break;
            case 'm':
                if (command.thirdArgument.empty || !command.fourthArgument.empty) {
                    fprintf(stderr, "ERROR %d\n", line);
                } else {
                    printf("%d\n", gamma_move(g, command.firstArgument.value, command.secondArgument.value,
                                              command.thirdArgument.value));
                }
                break;
            case ' ':
                break;
            default:
                fprintf(stderr, "ERROR %d\n", line);
        }
    }

    return g;
}