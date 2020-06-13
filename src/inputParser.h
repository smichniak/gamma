/** @file
 * Interfejs modułu, który odpowiada za interpretację wejścia programu.
 *
 * @author Szymon Michniak <s.michniak@student.uw.edu.pl>
 * @date 16.05.2020
 */

#ifndef GAMMA_INPUTPARSER_H
#define GAMMA_INPUTPARSER_H

#include "gamma.h"

/**
 * @struct argument_t
 * Struktura przechowująca informacje o argumencie funckji uzuskanym z wejścia programu.
*/
typedef struct {
    uint32_t value; ///< Wartość argumentu.
    bool valid; ///< @p true, jeśli argument jest prawidłowy, @p false w przeciwnym przypadku
    bool empty; ///< @p true, jeśli argument jest pusty, @p false w przeciwnym przypadku
} argument_t;

/**
 * @struct command_t
 * Struktura przechowująca informacje o poleceniu otrzymanym z wejścia
*/
typedef struct {
    char function; ///< Znak oznaczający funkcję, która ma zostać wywołana.
    argument_t first_argument; ///< Pierwszy argument polecenia
    argument_t second_argument; ///< Drugi argument polecenia
    argument_t third_argument; ///< Trzeci argument polecenia
    argument_t fourth_argument; ///< Czwarty argument polecenia
    bool is_valid; ///< @p true, jeśli komenda ma format zgody ze specyfikacją, @p false w przeciwnym przypadku
} command_t;

/** @brief Zwraca komedę zawartą w linii.
 * Rozdziela ciąg znaków na fragmęty między białymi znakami używając @p strtok, przypisuje fragmenty
 * do kolejnych argumentów funckji, decyduje o zgodności komendy ze specyfikacją, ignoruje linie puste
 * i zaczynające się na @p #
 * @param[in,out] line   – ciąg znaków, który zawiera komendę do przetworzenia.
 * @return Struktura opisująca koemdę do wywołania.
 */
command_t get_command(char* line);

/** @brief Wywołuje komendę.
 * Interpretuje komendę i w zależności od funckji, wypisuje jej wynik, przechodzi do trybu interaktywnego
 * lub wypisuje @p ERROR @p line jeśli wyowałnie jest błędne.
 * @param[in] command    – ciąg znaków, który zawiera komendę do przetworzenia,
 * @param[in,out] g_ptr   – wskaźnik na wskaźnik na strukturę przechowującą stan gry,
 * @param[in] line       – numer linii wejścia, z której została wywołana koemnda
 * @return Struktura opisująca komendę do wywołania.
 */
void execute_command(command_t command, gamma_t** g_ptr, unsigned long long line);

#endif /* GAMMA_INPUTPARSER_H */
