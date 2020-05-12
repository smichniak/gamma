#define _XOPEN_SOURCE 700

#include <stdio.h>


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "gamma.h"
#include "display.h"
#include "inputParser.h"

size_t INITIAL_BUFFER_SIZE = 0;

gamma_t* g = NULL;
char* line = NULL;

void exit_gamma() {
    gamma_delete(g);
    free(line);
}


int main() {
    atexit(exit_gamma);

    int lineNum = 1;

    while (getline(&line, &INITIAL_BUFFER_SIZE, stdin) > 0) {
        command_t command = getCommand(line);
        executeCommand(command, &g, lineNum);
        lineNum++;
        free(line);
        line = NULL;
    }



//    int i, j, n;
//
//    for (i = 0; i < 11; i++) {
//        for (j = 0; j < 10; j++) {
//            n = 10 * i + j;
//            if (n > 108) break;
//            printf("\033[%dm %3d\033[m", n, n);
//        }
//        printf("\n");
//    }
//    printf("\033[%dm HELLO \033[m\n", 7);
//    printf("HELLO\n");
//
//    gamma_t* g = gamma_new(3, 3, 30, 3);
//    gamma_move(g, 12, 1, 1);
//    char* board =  boardWithHighlight(g, true, 1, 1);
//    printf("%s",board);
//    free(board);
//
//    gamma_delete(g);



    return 0;


}