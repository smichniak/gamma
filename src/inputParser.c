#include "inputParser.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Valid characters in commands must have ASCII codes in range [33, 255]
const int MIN_ASCII = 33;
const int MAX_ASCII = 255;
//Whitespace characters that separate command arguments
const char WHITE_CHARS[] = " \t\v\f\r";
const char* VALID_FUNCTIONS = "BImgbfqp";

typedef struct {
    uint32_t value;
    bool valid;
} argument_t;


//Default command is valid and does nothing
command_t defaultCommand() {
    command_t defComamand;
    defComamand.function = ' ';
    defComamand.firstArgument = 0;
    defComamand.secondArgument = 0;
    defComamand.thirdArgument = 0;
    defComamand.isValid = true;
    return defComamand;
}

bool isWhite(char chracter) {
    for (uint32_t i = 0; i < strlen(WHITE_CHARS); ++i) {
        if (WHITE_CHARS[i] == chracter) {
            return true;
        }
    }
    return false;
}

bool isZero(char* string) {
    if (strlen(string) < 1) {
        return false;
    }
    for (uint32_t i = 0; i < strlen(string); ++i) {
        if (string[i] != '0') {
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
    argument.valid = true;

    uint32_t value = strtoul(string, NULL, 10);
    if (!isdigit(string[0]) || (value == 0 && !isZero(string))) {
        argument.valid = false;
    } else {
        argument.value = value;
    }

    return argument;
}


command_t getCommand(char* line) {
    command_t command = defaultCommand();

    if (line != NULL && line[0] != '#') {
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
            char* secondArg = strtok(NULL, WHITE_CHARS);
            char* thirdArg = strtok(NULL, WHITE_CHARS);
            char* fourthArg = strtok(NULL, WHITE_CHARS);
            char* restOfLine = strtok(NULL, WHITE_CHARS);

            if (function != NULL) {
                if (restOfLine != NULL || !validString(function) || !validString(firstArg) ||
                    !validString(secondArg) || !validString(thirdArg) || !validFunction(function)) {
                    //Valid line can't have more thant three arguments and each argument must be valid
                    command.isValid = false;
                } else {
                    command.function = function;
                    command.firstArgument = firstArg;
                    command.secondArgument = secondArg;
                    command.thirdArgument = thirdArg;
                }
            }
        }
    }
    return command;
}