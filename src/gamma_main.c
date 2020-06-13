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
    size_t initial_buffer_size = 0;

    atexit(exit_gamma);

    unsigned long long line_num = 1;

    while (getline(&line, &initial_buffer_size, stdin) > 0) {
        command_t command = get_command(line);
        execute_command(command, &g, line_num);
        line_num++;
        free(line);
        line = NULL;
    }


    return 0;
}
