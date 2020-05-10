#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <unistd.h>
#include <termios.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "gamma.h"
#include "inputParser.h"

size_t INITIAL_BUFFER_SIZE = 0;

void clear() {
    printf("\033[2J");
    printf("\033[H");
    printf("\033[1;1H");
    //  printf("\e[1;1H\e[2J");
}

int main() {
//    char* line = NULL;
//    gamma_t* g = NULL;
//    int lineNum = 1;
//
//    while (getline(&line, &INITIAL_BUFFER_SIZE, stdin) > 0) {
//        command_t command = getCommand(line);
//        g = executeCommand(command, g, lineNum);
//        lineNum++;
//        free(line);
//        line = NULL;
//    }
//    free(line);
//
//    gamma_delete(g);

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

    clear();
    char k = '\0';

    while (1) {

        if (k == 'g') {
            printf("GOLDEN MOVE\n");
        }
        // clear();
        k = getchar();
        if (k == 'k') {
            break;
        }

        if (k == '\033') { // if the first value is esc
            if (getchar() == '[') {
                switch (getchar()) { // the real value
                    case 'A':
                        // code for arrow up
                        printf("UP\n");
                        break;
                    case 'B':
                        // code for arrow down
                        printf("Down\n");
                        break;
                    case 'C':
                        // code for arrow right
                        printf("right\n");
                        break;
                    case 'D':
                        // code for arrow left
                        printf("left\n");
                        break;
                }
            }
        }

    }

    a = tcsetattr(STDIN_FILENO, TCSANOW, &original);
    if (a != 0) {
        exit(1);
    }

    return 0;


}