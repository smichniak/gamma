/** @file
 * Implementacja modułu inputParser.h
 *
 * @author Szymon Michniak <s.michniak@student.uw.edu.pl>
 * @date 17.05.2020
 */

#include <inttypes.h>
#include <sys/ioctl.h>
#include "display.h"
#include "inputParser.h"


/** Białe znaki, które oddzialają parametry funckji.
 */
static const char WHITE_CHARS[] = " \t\v\f\r";

/** Ciąg znaków, które oznaczją poprawne funkcje i funkcję pustą.
 */
static const char VALID_FUNCTIONS[] = "BImgbfqp ";

/** Liczba wierszy, którą na ekranie zajmują informacje o graczu.
 */
static const int PLAYER_INFORMATION_HEIGHT = 6;

/**
 * @struct result_t
 * Struktura przechowująca informacje o wyniku funkcji, która zwraca @p uint64_t.
*/
typedef struct {
    uint64_t result_value; ///< Wartość, którą funckja zwróciła
    bool valid; ///< @p false, jeśli wywołanie funckji było nieprawidłowe, @p true w przeciwnym przypadku
} result_t;


/** @brief Sprawdza, czy ciąg znaków oznacza poprawną funckję.
 * Sprawdza, czy ciąg znaków jest poprwaną funckją gry @p gamma. Funkcja musi być jednoznakowa, i znak
 * ten musi być jednym z ustalonych w @p VALID_FUNCTIONS.
 * @param[in] function   – ciąg znaków do sprawdzenia.
 * @return @p true, jeśli funckja jest prawidłowa, @p false w przeciwnym przypadku
 */
static bool valid_function(char* function) {
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

/** @brief Sprawdza, czy ciąg znaków oznacza poprawnym argumentem funkcji.
 * Sprawdza, czy ciąg znaków jest argumentem funkcji gry @p gamma. Argument musi zawierać jednynie
 * cryfry i dać się poprawnie skonwertować na typ @p uint32_t. Jeśli @p string jest równy @p NULL,
 * to argument jest pusty.
 * @param[in] string   – ciąg znaków do sprawdzenia.
 * @return Struktura opisująca argument funkcji.
 */
static argument_t valid_argument(char* string) {
    argument_t argument;
    argument.value = 0;
    argument.valid = true;
    argument.empty = false;

    if (string == NULL) {
        argument.empty = true;
    } else if (!only_digits(string)) {
        // Argument może zawierać tylko cyfry, żeby był poprawny
        argument.valid = false;
    } else {
        uint64_t conversion = strtoul(string, NULL, 10);
        if (conversion > UINT32_MAX) {
            // Wynik większy od UINT32_MAX nie jest poprawny
            argument.valid = false;
        } else {
            argument.value = conversion;
        }

    }

    return argument;
}

/** @brief Wskazuje następnego gracza, który może wykonać ruch.
 * Sprawdza kolejych gracz po @p current_player. Zwraca następnego, który może wykonać ruch. Jeśli
 * liczba pominiętych graczy jest większa, niż liczba wszystkich graczy, to nikt nie może już wykonać
 * ruchu.
 * @param[in] g              – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] current_player  – numer gracza, którego tura się skończyła, liczba dodatnia niewiększa od wartości
 *                              @p players z funkcji @ref gamma_new,
 * @param[in] players_skipped – liczba pominiętych graczy, przy pierwszym wywołaniu zawsze wynosi 0
 * @return Numer następnego gracza, który może wykonać ruch, lub @p 0 jeśli żaden gracz nie może już
 * wykonać ruchu.
 */
static uint32_t get_next_player(gamma_t* g, uint32_t current_player, uint64_t players_skipped) {
    // Jeśli sprawdziliśmy wszytskich graczy i żaden nie może wykonać ruchu, to zwracamy 0
    if (players_skipped > get_players(g)) {
        return 0;
    }
    uint32_t max_player = get_players(g);
    // Po ostatnim graczu wracamy do nr 1
    uint32_t next_player = (current_player % max_player) + 1;

    // Jeśli aktualny gracz nie może wykonać ruchu, sprawdzamy następnego
    if (gamma_free_fields(g, next_player) == 0 && !gamma_golden_possible(g, next_player)) {
        return get_next_player(g, next_player, players_skipped + 1);
    }
    return next_player;
}

/** @brief Wykonuje akcje po naciśnięciu strzałki w trybie interaktywnym.
 * Sprawdza, czy w trybie interaktywnym została wciśnięta strzałka, jeśli tak,
 * to przesuwa kursor odpowiednio.
 * @param[in, out] cursor_x_ptr   – wskaźnik na współrzędną @p x kursora,
 * @param[in, out] cursor_y_ptr   – wskaźnik na współrzędną @p y kursora,
 * @param[in] max_x               – maksymalna współrzędna @p x,
 * @param[in] max_y               – maksymalna współrzędna @p y,
 * @param[in, out] input_char_ptr – wskaźnik na znak z wejścia, który ma być zinterpretowany.

 */
static void parse_arrows(uint32_t* cursor_x_ptr, uint32_t* cursor_y_ptr, uint32_t max_x, uint32_t max_y, int* input_char_ptr) {
    *input_char_ptr = getchar();
    if (*input_char_ptr == '[') {
        *input_char_ptr = getchar();
        if (*input_char_ptr == 'A') { // Strzałak w górę
            if (*cursor_y_ptr != max_y) {
                (*cursor_y_ptr)++;
            }
            *input_char_ptr = 0;
        } else if (*input_char_ptr == 'B') { // Strzałka w dół
            if (*cursor_y_ptr != 0) {
                (*cursor_y_ptr)--;
            }
            *input_char_ptr = 0;
        } else if (*input_char_ptr == 'C') { // Strzałka w prawo
            if (*cursor_x_ptr != max_x) {
                (*cursor_x_ptr)++;
            }
            *input_char_ptr = 0;
        } else if (*input_char_ptr == 'D') { // Strzałka w lewo
            if (*cursor_x_ptr != 0) {
                (*cursor_x_ptr)--;
            }
            *input_char_ptr = 0;
        }
    }
}

/** @brief Interpretuje wejście trybu interaktywnego.
 * Ustawia tryb wejścia na "raw", zaczyna od gracza nr 1 i ustawia wskaźnik na pole (0, 0). Wywołuje
 * funkcje w zależności od wejścia zgodnie ze specyfikacją gry gamma. Przerywa po wykryciu na wejściu
 * znaku o kodzie 4 (ctrl + D) lub gdy żaden gracz nie może wykonać ruchu. Wypisuje podsumowanie gry i
 * przywraca oryginalne ustawienia terminala.
 * @param[in,out] g – wskaźnik na strukturę przechowującą stan gry.
 */
static void interactive_input(gamma_t* g) {
    uint32_t cursor_x = 0;
    uint32_t cursor_y = 0;
    uint32_t max_x = get_width(g) - 1;
    uint32_t max_y = get_height(g) - 1;
    uint32_t current_player = 1;
    bool next_player;
    int input_character = 0;

    change_terminal_to_raw();
    while (current_player != 0) {
        next_player = false;

        clear();
        print_with_highlight(g, cursor_x, cursor_y, 0, current_player);
        print_player_info(g, current_player);

        // input_character == 0 wtedy, gdy poprzedni wczytany znak został już zinterpretowany
        if (input_character == 0) {
            input_character = getchar();
        }

        if (input_character == '\033') { // Początek kodu strzałek
            parse_arrows(&cursor_x, &cursor_y, max_x, max_y, &input_character);
        } else if (input_character == ' ') {
            next_player = gamma_move(g, current_player, cursor_x, cursor_y);
            input_character = 0;
        } else if (input_character == 'g' || input_character == 'G') {
            next_player = gamma_golden_move(g, current_player, cursor_x, cursor_y);
            input_character = 0;
        } else if (input_character == 'c' || input_character == 'C') {
            input_character = 0;
            next_player = true;
        } else if (input_character == 4) { // Koniec transmisji, gracz = 0 kończy tryb interaktywny
            current_player = 0;
        } else { // Znak, który nie odpowiada żadnaje komendzie
            input_character = 0;
        }

        if (next_player) {
            current_player = get_next_player(g, current_player, 0);
        }
    }

    // Na koniec gry wypisujemy planszę i podsumowanie wyników
    clear();
    print_with_highlight(g, 0, 0, 0, current_player);
    print_results(g);
    exit_interactive(0);
}

/** @brief Zwraca domyślną komendę.
 * Zwraca strukturę domyślnej komendy. Jest ona poprawna, ma puste argumenty i nie powoduje żadnego działania.
 * @return Struktura opisująca domyślną komendę.
 */
static command_t def_command() {
    command_t command;
    command.function = ' ';
    command.is_valid = true;
    command.first_argument = valid_argument("");
    command.second_argument = valid_argument("");
    command.third_argument = valid_argument("");
    command.fourth_argument = valid_argument("");
    return command;
}

command_t get_command(char* line) {
    command_t command = def_command();

    // Pomijamy linie puste i zaczynajace się od #
    if (line != NULL && line[0] != '#' && line[0] != '\n') {
        if (strlen(line) == 0 || isspace(line[0]) || line[strlen(line) - 1] != '\n') {
            // Błędne są linie nie kończące się znakiem nowej linii i rozpoczynające się białym znakiem
            command.is_valid = false;
        } else {
            // Usuwamy '\n' z końca linii
            line[strlen(line) - 1] = 0;

            // Rozdzielamy części miedzy białymi znakami
            char* function = strtok(line, WHITE_CHARS);

            char* first_arg = strtok(NULL, WHITE_CHARS);
            argument_t first_argument = valid_argument(first_arg);

            char* second_arg = strtok(NULL, WHITE_CHARS);
            argument_t second_argument = valid_argument(second_arg);

            char* third_arg = strtok(NULL, WHITE_CHARS);
            argument_t third_argument = valid_argument(third_arg);

            char* fourth_arg = strtok(NULL, WHITE_CHARS);
            argument_t fourth_argument = valid_argument(fourth_arg);

            char* rest_of_line = strtok(NULL, WHITE_CHARS);

            if (function != NULL) {
                if (rest_of_line != NULL || !valid_function(function) || !first_argument.valid ||
                    !second_argument.valid || !third_argument.valid || !fourth_argument.valid) {
                    // Prawidłowa linia nie może mieć więcej niż 4 argumenty i każdy musi być poprawny
                    command.is_valid = false;
                } else {
                    command.function = function[0];
                    command.first_argument = first_argument;
                    command.second_argument = second_argument;
                    command.third_argument = third_argument;
                    command.fourth_argument = fourth_argument;
                }
            }
        }
    }


    return command;
}

/** @brief Wywołuje daną komendę w grze danej wskaźnikiem.
 * Wywołuje jedną z funkcji {@p m, @p g, @p b, @p f, @p q} i wynik wywołania zapisuje w strukturze, która
 * jest zwracana.
 * @param[in,out] g_ptr   – wskaźnik na wskaźnik na strukturę przechowującą stan gry,
 * @param[in] command    – struktura opisująca komendę do wywoałnia.
 * @return Struktura opisująca wynik wywołania. Parametr poprawności ustawiony na @p true, jeśli udało się
 * wyowałać funkcję, @p false w przeciwnym przypadku.
 */
static result_t function_result(gamma_t** g_ptr, command_t command) {
    result_t result;
    result.valid = true;

    if (!command.fourth_argument.empty || !*g_ptr) {
        result.valid = false;
    } else if (command.function == 'm') { // Zwykly ruch, trzy argumenty
        if (command.third_argument.empty) {
            result.valid = false;
        } else {
            result.result_value = gamma_move(*g_ptr, command.first_argument.value, command.second_argument.value,
                                             command.third_argument.value);
        }
    } else if (command.function == 'g') { // Złoty ruch, trzy argumenty
        if (command.third_argument.empty) {
            result.valid = false;
        } else {
            result.result_value = gamma_golden_move(*g_ptr, command.first_argument.value,
                                                    command.second_argument.value, command.third_argument.value);
        }
    } else if (!command.second_argument.empty || command.first_argument.empty) {
        result.valid = false;
    } else if (command.function == 'b') { // Zajęte pola, jeden argument
        result.result_value = gamma_busy_fields(*g_ptr, command.first_argument.value);
    } else if (command.function == 'f') { // Wolne pola, jeden argument
        result.result_value = gamma_free_fields(*g_ptr, command.first_argument.value);
    } else if (command.function == 'q') { // Czy możliwy złoty ruch, jeden argument
        result.result_value = gamma_golden_possible(*g_ptr, command.first_argument.value);
    }

    return result;
}

/** @brief Sprawdza, czy plansza zmieści się na ekranie.
 * Sprawdza rozmiary terminala i porównuje je z rozmiarami planszy. Jeśli plansza
 * jest zbyt duża, to wypisuje stosowny komunikat
 * o błędzie i kończy program z kodem wyjścia @p 1.
 * @param[in,out] g – wskaźnik na strukturę przechowującą stan gry.
 */
static void check_terminal_size(gamma_t* g) {
    struct winsize window;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &window) == -1) {
        exit(1);
    }
    uint32_t rows = window.ws_row;
    uint32_t columns = window.ws_col;

    if (get_height(g) + PLAYER_INFORMATION_HEIGHT > rows || get_width(g) > columns) {
        fprintf(stderr, "Terminal to small to display the board.\n");
        exit(1);
    }
}

void execute_command(command_t command, gamma_t** g_ptr, unsigned long long line) {
    if (!command.is_valid) {
        print_error(line);
    } else if (command.function == ' ') { // Pusta komenda, nic nie robi
    } else if (command.function == 'B' || command.function == 'I') {
        if (*g_ptr) { // Nie możemy zacząć nowej gry, jeśli już jakaś trwa
            print_error(line);
        } else {
            gamma_t* new_gamma = gamma_new(command.first_argument.value, command.second_argument.value,
                                           command.third_argument.value, command.fourth_argument.value);
            if (!new_gamma) { // Błędne argumenty lub problemy z alokacją nowej gry
                print_error(line);
            } else if (command.function == 'B') {
                *g_ptr = new_gamma;
                printf("OK %llu\n", line);
            } else {
                *g_ptr = new_gamma;
                check_terminal_size(new_gamma);
                interactive_input(new_gamma);
            }
        }

    } else if (command.function == 'p') { // Ciąg znaków opisujący planszę, zero argumentów
        if (!command.first_argument.empty) {
            print_error(line);
        } else {
            // current_player = 0 oznaczaja string planszy bez podświetlonych pól
            print_with_highlight(*g_ptr, 0, 0, line, 0);
        }

    } else {
        result_t result = function_result(g_ptr, command);
        if (!result.valid) {
            print_error(line);
        } else {
            printf("%" PRIu64 "\n", result.result_value);
        }
    }
}