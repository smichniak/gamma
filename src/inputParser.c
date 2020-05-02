#include "inputParser.h"
#include <string.h>
#include <stdbool.h>

//Valid characters in commands must have ASCII codes in range [33, 255]
const int MIN_ASCII = 33;
const int MAX_ASCII = 255;
//Whitespace characters that separate command arguments
const char WHITE_CHARS[] = " \t\v\f\r";
const char* VALID_FUNCTIONS = "BImgbfqp";


//Default command is valid and does nothing
Command defaultCommand() {
    Command defComamand;
    defComamand.function = NULL;
    defComamand.firstArgument = NULL;
    defComamand.secondArgument = NULL;
    defComamand.thirdArgument = NULL;
    defComamand.isValid = true;
    return defComamand;
}

bool validFunction(char* function) {
    if (strlen(function) > 1) {
        return false;
    }

    for (int i = 0; i < (int) strlen(VALID_FUNCTIONS); ++i) {
        if (VALID_FUNCTIONS[i] == function[0]) {
            return true;
        }
    }
    return false;
}

bool validString(char* string) {
    if (string == NULL) {
        return true;
    } else {
        int isValid = true;

        //Unsigned string for proper extended ASCII handling
        unsigned char* unsignedString = (unsigned char*) string;
        for (int i = 0; i < (int) strlen(string); ++i) {
            //Every char in string must be in given range
            isValid = isValid && unsignedString[i] >= MIN_ASCII && unsignedString[i] <= MAX_ASCII;
        }
        return isValid;
    }
}


Command getCommand(char* line) {
    Command command = defaultCommand();

    if (line != NULL && line[0] != '#') {
        if (line[strlen(line) - 1] != '\n') {
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