//TODO
//Check on students if necessary
#define _XOPEN_SOURCE 700

#include "inputParser.h"

//Line buffer is dynamically allocated
size_t INITIAL_BUFFER_SIZE = 0;

//Globalne zmienne, by można było je zwolnić w exit_gamma
gamma_t* g = NULL;
char* line = NULL;


/** @brief Funkcja wywoływana przy zakończeniu programu.
 *  Zwalnia pamięć zaalokowaną na wskaźnikach @ref g i @ref line.
 */
void exit_gamma() {
    gamma_delete(g);
    free(line);
}

int main() {
    atexit(exit_gamma);

    unsigned long long lineNum = 1;

    while (getline(&line, &INITIAL_BUFFER_SIZE, stdin) > 0) {
        command_t command = getCommand(line);
        executeCommand(command, &g, lineNum);
        lineNum++;
        free(line);
        line = NULL;
    }

    return 0;
}
