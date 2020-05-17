/** @file
 * Główny plik obsługujący grę gamma.
 *
 * @author Szymon Michniak <s.michniak@student.uw.edu.pl>
 * @date 16.05.2020
 */

#include "inputParser.h"


//Globalne zmienne, by można było je zwolnić w exit_gamma

/** Wskaźnik na strukturę przechowującą stan gry.
 */
gamma_t* g = NULL;

/** Ciąg znaków, które są zawarte w jednej linii wejścia.
 */
char* line = NULL;


/** @brief Funkcja wywoływana przy zakończeniu programu.
 *  Zwalnia pamięć zaalokowaną na wskaźnikach @ref g i @ref line.
 */
void exit_gamma() {
    gamma_delete(g);
    free(line);
}

int main() {
    //Początkowy rozmiar bufora na wejście
    size_t initialBufferSize = 0;

    atexit(exit_gamma);

    unsigned long long lineNum = 1;

    while (getline(&line, &initialBufferSize, stdin) > 0) {
        command_t command = getCommand(line);
        executeCommand(command, &g, lineNum);
        lineNum++;
        free(line);
        line = NULL;
    }

    return 0;
}
