#include "inputParser.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "display.h"

#include <unistd.h>
#include <termios.h>

//Whitespace characters that separate command arguments
const char WHITE_CHARS[] = " \t\v\f\r";
const char VALID_FUNCTIONS[] = "BImgbfqp ";

typedef struct result {
    uint64_t resultValue;
    bool valid;
} result_t;

bool isWhite(char character) {
    for (uint32_t i = 0; i < strlen(WHITE_CHARS); ++i) {
        if (WHITE_CHARS[i] == character) {
            return true;
        }
    }
    return false;
}

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

struct termios changeTerminalToRaw() {
    struct termios original, raw;

    // Save original serial communication configuration for stdin
    int a = tcgetattr(STDIN_FILENO, &original);
    if (a != 0) {
        exit(1);
    }
    raw = original;

    raw.c_lflag &= ~(ICANON | ECHO);
    a = tcsetattr(STDIN_FILENO, TCSANOW, &raw);
    if (a != 0) {
        exit(1);
    }
    return original;
}

uint32_t nextPlayer(gamma_t* g, uint32_t currentPlayer, uint32_t startPlayer) {
    uint32_t maxPlayer = get_players(g);
    currentPlayer = (currentPlayer % maxPlayer) + 1;
    if (currentPlayer == startPlayer) {
        return 0;
    }
    if (gamma_free_fields(g, currentPlayer) == 0 && !gamma_golden_possible(g, currentPlayer)) {
        return nextPlayer(g, currentPlayer, startPlayer);
    }
    return currentPlayer;

}

void interactiveInput(gamma_t* g) {
    uint32_t x = 0;
    uint32_t y = 0;
    uint32_t maxX = get_width(g) - 1;
    uint32_t maxY = get_height(g) - 1;
    uint32_t currentPlayer = 1;
    bool result;

    struct termios originalTerminal = changeTerminalToRaw();

    clear();
    char k = '\0';

    while (currentPlayer != 0) {
        result = false;
        clear();
        printf("%s", boardWithHighlight(g, true, x, y));
        printf("PLAYER %u %llu %llu\n", currentPlayer, get_busy_fields(g, currentPlayer), get_free_fields(g));
        k = getchar();

        if (k == '\033') { // if the first value is esc
            if (getchar() == '[') {
                switch (getchar()) { // the real value
                    case 'A':
                        // code for arrow up
                        if (y != maxY) {
                            y++;
                        }
                        break;
                    case 'B':
                        // code for arrow down
                        if (y != 0) {
                            y--;
                        }
                        break;
                    case 'C':
                        // code for arrow right
                        if (x != maxX) {
                            x++;
                        }
                        break;
                    case 'D':
                        // code for arrow left
                        if (x != 0) {
                            x--;
                        }
                        break;
                }
                //clear();
                //printf("%s", boardWithHighlight(g, true, x, y));
            }
        } else if (k == ' ') {
            result = gamma_move(g, currentPlayer, x, y);
        } else if (k == 'g' || k == 'G') {
            result = gamma_golden_move(g, currentPlayer, x, y);
        } else if (k == 4) {
            break;
        }
        if (result || k == 'c' || k == 'C') {
            currentPlayer = nextPlayer(g, currentPlayer, currentPlayer);
        }
    }
    clear();
    printf("%s", boardWithHighlight(g, false, 0, 0));
    printResults(g);

    int a = tcsetattr(STDIN_FILENO, TCSANOW, &originalTerminal);
    if (a != 0) {
        exit(1);
    }

    exit(0);
}

command_t defCommand() {
    command_t command;
    command.function = ' ';
    command.isValid = true;
    command.firstArgument = validArgument("");
    command.secondArgument = validArgument("");
    command.thirdArgument = validArgument("");
    command.fourthArgument = validArgument("");
    return command;
}

command_t getCommand(char* line) {
    command_t command = defCommand();

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

result_t functionResult(gamma_t** g, command_t command) {
    result_t result;
    result.valid = true;

    if (!command.fourthArgument.empty || !*g) {
        result.valid = false;

    } else if (command.function == 'm') {
        if (command.thirdArgument.empty) {
            result.valid = false;
        } else {
            result.resultValue = gamma_move(*g, command.firstArgument.value, command.secondArgument.value,
                                            command.thirdArgument.value);
        }

    } else if (command.function == 'g') {
        if (command.thirdArgument.empty) {
            result.valid = false;
        } else {
            result.resultValue =
                    gamma_golden_move(*g, command.firstArgument.value, command.secondArgument.value,
                                      command.thirdArgument.value);
        }
    } else if (!command.secondArgument.empty || command.firstArgument.empty) {
        result.valid = false;
    } else if (command.function == 'b') {
        result.resultValue = gamma_busy_fields(*g, command.firstArgument.value);
    } else if (command.function == 'f') {
        result.resultValue = gamma_free_fields(*g, command.firstArgument.value);
    } else if (command.function == 'q') {
        result.resultValue = gamma_golden_possible(*g, command.firstArgument.value);
    }

    return result;
}

void printError(int line) {
    fprintf(stderr, "ERROR %d\n", line);
}

void executeCommand(command_t command, gamma_t** g, int line) {
    if (!command.isValid) {
        printError(line);
    } else if (command.function == ' ') { //Do nothing
    } else if (command.function == 'B' || command.function == 'I') {
        if (*g) {
            printError(line);
        } else {
            gamma_t* new_gamma = gamma_new(command.firstArgument.value, command.secondArgument.value,
                                           command.thirdArgument.value, command.fourthArgument.value);
            if (!new_gamma) {
                printError(line);
            } else if (command.function == 'B') {
                *g = new_gamma;
                printf("OK %d\n", line);
            } else {
                interactiveInput(new_gamma);
            }
        }

    } else if (command.function == 'p') {
        if (!command.firstArgument.empty) {
            printError(line);
        } else {
            char* board = gamma_board(*g);
            if (!board) {
                printError(line);
            } else {
                printf("%s", board);
                free(board);
            }
        }

    } else {
        result_t result = functionResult(g, command);
        if (!result.valid) {
            printError(line);
        } else {
            printf("%llu\n", result.resultValue);
        }
    }

}