/** @file
 * Główny plik obsługujący grę gamma.
 *
 * @author Szymon Michniak <s.michniak@student.uw.edu.pl>
 * @date 16.05.2020
 */

/** Makro naprawia "implicit declaration of function ‘getline’"
 */
#define _XOPEN_SOURCE 700

#include "inputParser.h"

// Globalne zmienne, by można było je zwolnić w exit_gamma
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

/** @brief Uruchamia pareser wejścia.
 * Uruchamia parser wejścia do programu, wczytuje wejście linia po linii, interpretuje te linie jako komendy
 * i je wywołuje.
 */
int main() {
    // Początkowy rozmiar bufora na wejście, bufor na linię będzie dynamicznie zmieniany
    size_t initialBufferSize = 0;

    atexit(exit_gamma);

    unsigned long long lineNum = 1;

    while (getline(&line, &initialBufferSize, stdin) > 0) {
        command_t command = get_command(line);
        execute_command(command, &g, lineNum);
        lineNum++;
        free(line);
        line = NULL;
    }

//    gamma_t* g = gamma_new(5, 5, 5, 5);
//    printf("%d", move_possible(g, 1, 0, 0));
//    printf("%d", move_possible(g, 1, 0, 1));
//    printf("%d", move_possible(g, 1, 0, 2));
//    printf("%d", move_possible(g, 1, 0, 3));
//    printf("%d", move_possible(g, 1, 0, 4));
//    printf("%d", move_possible(g, 1, 1, 2));

    return 0;
}
