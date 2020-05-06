#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "inputParser.h"

size_t INITIAL_BUFFER_SIZE = 0;

int main() {
   /* char* line = NULL;

    while (getline(&line, &INITIAL_BUFFER_SIZE, stdin) > 0) {
        command_t command = getCommand(line);
        printf("%s ", command.function);
        printf("%u", command.firstArgument);


        free(line);
        line = NULL;
    }
    free(line);*/

   char* str = "123";
   uint32_t i = strtoul(str, NULL, 10);
   printf("%ul", i);



    return 0;


}