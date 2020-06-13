/** @file
 * Implementacja modułu display.h
 *
 * @author Szymon Michniak <s.michniak@student.uw.edu.pl>
 * @date 16.05.2020
 */

#include <inttypes.h>
#include <string.h>
#include "display.h"

/** Kod zmiany koloru tekstu na zielony.
 */
static const char* GREEN_TEXT = "\e[0;32m";

/** Kod zmiany koloru tekstu na czerwony.
 */
static const char* RED_TEXT = "\e[0;31m";

/** Kod zmiany koloru podświetlenia na zielony.
 */
static const char* GREEN_BACKGROUND = "\e[42m";

/** Kod zmiany koloru podświetlenia na czerwony.
 */
static const char* RED_BACKGROUND = "\e[41m";

/** Kod zmiany koloru podświetlenia na żółty.
 */
static const char* YELLOW_BACKGROUND = "\e[43m";

/** Kod przywrawcający domyślny kolor.
 */
static const char* END_HIGHLIGHT = "\033[m";

/** Liczba znaków w kodzie początku i końca zmiany koloru.
 */
static const int CODE_LENGTH = 10;

// Zmienna globalna, by można było z niej korzystać w razie potrzeby w change_terminal_to_original, które jest
// wywoływana w exit_interactive
/** Struktura przechowująca informacje o ustawieniach terminala.
 */
static struct termios original;

inline void clear() {
    printf("\033[2J");
    printf("\033[H");
}

void change_terminal_to_raw() {
    struct termios raw;

    // Zachowuje oryginalne ustawienia terminala
    if (tcgetattr(STDIN_FILENO, &original) != 0) {
        exit(1);
    }
    // Tworzy kopię ustawień i zmienia je na wejscie "raw"
    raw = original;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSANOW, &raw) != 0) {
        exit(1);
    }
    // Ukrywa kursor
    printf("\e[?25l");
}

void change_terminal_to_original() {
    // Pokazuje kursor
    printf("\e[?25h");
    if (tcsetattr(STDIN_FILENO, TCSANOW, &original) != 0) {
        exit(1);
    }
}

void exit_interactive(int code) {
    change_terminal_to_original();
    exit(code);
}

/** @brief Zwraca największego gracza na planszy.
 * Przeszukuje tablice zajętych pól i zwraca największego gracza z niezerową liczbą zajętych pól.
 * @param[in] g       – wskaźnik na strukturę przechowującą st
 * an gry.
 * @return Numer największego gracza, który ma pionek na planszy.
 */
static uint32_t max_player_on_board(gamma_t* g) {
    for (uint32_t player = get_players(g); player > 0; --player) {
        if (gamma_busy_fields(g, player) > 0) {
            return player;
        }
    }
    return 0;
}

/** @brief Dodaje kod podświetlenie do napisu planszy.
 * Dodaje kod podświetlenie jako napis na końcu tablicy znaków reprezentującej planszę.
 * @param[in, out] board_string - tablica znaków, napis reprezentujący planszę.
 * @param[in, out] string_index - indeks ostatniego wolnego miejsca w tablicy znaków,
 * @param[in] highlight        – ANSI escape code, który odpowiada za zmianę koloru tła.
 * @return Indeks ostatniego wolnego miejsca w tablicy znaków, po dodaniu napisu.
 */
static size_t add_highlight(char* board_string, size_t string_index, const char* highlight) {
    for (uint32_t k = 0; k < strlen(highlight); ++k) {
        board_string[string_index] = highlight[k];
        string_index++;
    }
    return string_index;
}

/** @brief Dodaje spacje do napisu planszy.
 * Dodaje spacje na końcu tablicy znaków reprezentującej planszę.
 * @param[in, out] board_string - tablica znaków, napis reprezentujący planszę.
 * @param[in, out] string_index - indeks ostatniego wolnego miejsca w tablicy znaków,
 * @param[in] spaces           – liczba spacji do dodania.
 * @return Indeks ostatniego wolnego miejsca w tablicy znaków, po dodaniu napisu.
 */
static size_t add_spaces(char* board_string, size_t string_index, int spaces) {
    for (int space_index = 0; space_index < spaces; ++space_index) {
        board_string[string_index] = ' ';
        string_index++;
    }
    return string_index;
}

/** @brief Dodaje gracza do napisu planszy.
 * Dodaje numer gracza jako napis na końcu tablicy znaków reprezentującej planszę, napis gracza uzupełnia
 * pustymi znakami, by miał taką długość, jak długość napisu największego gracza na planszy. Opcjonalnie
 * podświetla tło danego pola, na którym znajduje się dodawany gracz.
 * @param[in] g                – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] column           – numer kolumny, liczba nieujemna mniejsza od wartości @p width z funkcji
 *                               @ref gamma_new,
 * @param[in] row              – numer wiersza, liczba nieujemna mniejsza od wartości @p height z funkcji
 *                               @ref gamma_new.
 * @param[in] max_player_digits  - liczba cyfr największego gracza,
 * @param[in, out] string_index - indeks ostatniego wolnego miejsca w tablicy znaków,
 * @param[in, out] board_string - tablica znaków, napis reprezentujący planszę.
 * @param[in] highlight         - @p true jeśli pole ma być podświetlone, @p false w przeciwnym przypadku
 * @return Indeks ostatniego wolnego miejsca w tablicy znaków, po dodaniu napisu.
 */
static size_t add_to_board(gamma_t* g, uint32_t column, uint32_t row, int max_player_digits, size_t string_index,
                           char* board_string, uint32_t current_player) {
    uint32_t player_on_field = get_player_on_field(g, column, row);
    int player_digits = digits(player_on_field);

    char* player_string;
    // +1 dla \0
    player_string = calloc(player_digits + (current_player > 0) * CODE_LENGTH + 1, sizeof(char));
    if (!player_string) {
        return 0;
    }

    player_on_field == 0 ? player_string[0] = '.' : sprintf(player_string, "%u", player_on_field);

    if (current_player > 0) {
        if (move_possible(g, current_player, column, row)) {
            string_index = add_highlight(board_string, string_index, GREEN_BACKGROUND);
        } else if (golden_possible_on_field(g, current_player, column, row)) {
            string_index = add_highlight(board_string, string_index, YELLOW_BACKGROUND);
        } else {
            string_index = add_highlight(board_string, string_index, RED_BACKGROUND);
        }
    }

    // Dodajemy napis numeru gracza
    for (int digit_index = 0; digit_index < player_digits; ++digit_index) {
        board_string[string_index] = player_string[digit_index];
        string_index++;
        max_player_digits--;
    }
    if (current_player > 0) {
        string_index = add_highlight(board_string, string_index, END_HIGHLIGHT);
    }

    // Pozostale znaki uzupełniamy spacjami
    string_index = add_spaces(board_string, string_index, max_player_digits);

    free(player_string);
    return string_index;
}

char* board_with_highlight(gamma_t* g, uint32_t x, uint32_t y, uint32_t current_player) {
    if (!g) {
        return NULL;
    }
    uint32_t width = get_width(g);
    uint32_t height = get_height(g);

    uint32_t max_player = max_player_on_board(g);
    int max_player_digits = digits(max_player);

    // Jeśli na planszy są gracze co najmniej dwucyfrowi, to między każdym gracze robię odstęp
    uint64_t spaces = max_player_digits == 1 ? 0 : width * height;

    char* board_string;
    // +height na \n po każdym rzędzie, +1 na \0
    board_string = calloc(max_player_digits * (uint64_t) width * (uint64_t) height + spaces + height +
                          (current_player > 0) * CODE_LENGTH + 1, sizeof(char));
    if (!board_string) {
        return NULL;
    }

    size_t string_index = 0;
    for (uint32_t row = height - 1; row < height; --row) {
        for (uint32_t column = 0; column < width; ++column) {
            // Decydujemy, czy jesteśmy w polu, które należy podświetlić
            string_index = add_to_board(g, column, row, max_player_digits, string_index, board_string,
                                        current_player * (column == x && row == y));
            if (string_index == 0) {
                free(board_string);
                return NULL;
            }

            string_index = add_spaces(board_string, string_index, spaces > 0);
        }
        // \n po każdym rzędzie
        board_string[string_index] = '\n';
        string_index++;
    }
    board_string[string_index] = '\0';
    return board_string;
}

void print_with_highlight(gamma_t* g, uint32_t x, uint32_t y, unsigned long long line, uint32_t current_player) {
    char* board = board_with_highlight(g, x, y, current_player);
    if (!board) {
        if (line == 0) {
            // Jesteśmy w trybie interaktywnym i chcemy z niego wyjść
            exit_interactive(1);
        } else {
            // Jesteśmy w trybie wsadowym, wypisujemy ERROR i dalej przyjmujemy wejście
            print_error(line);
        }
    } else {
        printf("%s", board);
        free(board);
    }
}

void print_results(gamma_t* g) {
    uint32_t players = get_players(g);
    printf("\nPLAYER: NUMBER - OCCUPIED FILEDS\n");
    uint64_t winner_fields = 0;
    for (uint32_t player = 1; player <= players; ++player) {
        uint64_t busy_fields = gamma_busy_fields(g, player);
        winner_fields =  busy_fields > winner_fields ? busy_fields : winner_fields;
    }
    for (uint32_t player = 1; player <= players; ++player) {
        if (gamma_busy_fields(g, player) == winner_fields) {
            printf("%s", GREEN_TEXT);
        }
        printf("PLAYER: %u - %" PRIu64 "\n", player, gamma_busy_fields(g, player));
        if (gamma_busy_fields(g, player) == winner_fields) {
            printf("%s", END_HIGHLIGHT);
        }
    }
}

inline void print_error(unsigned long long line) {
    fprintf(stderr, "ERROR %llu\n", line);
}

void print_player_info(gamma_t* g, uint32_t player) {
    printf("PLAYER: %u\n", player);
    uint32_t player_areas = get_player_areas(g, player);
    uint32_t max_areas = get_areas(g);
    printf("AREAS: ");
    if (player_areas == max_areas) {
        printf("%s", RED_TEXT);
    } else {
        printf("%s", GREEN_TEXT);
    }
    printf("%u/%u %s \n", player_areas, max_areas, END_HIGHLIGHT);
    printf("OCCUPIED FIELDS: %" PRIu64, gamma_busy_fields(g, player));
    printf("\nFREE FIELDS: %" PRIu64, gamma_free_fields(g, player));
    printf("\nGOLDEN MOVE AVAILABLE: ");
    if (gamma_golden_possible(g, player)) {
        printf("%s true %s \n", GREEN_TEXT, END_HIGHLIGHT);
    } else {
        printf("%s false %s \n", RED_TEXT, END_HIGHLIGHT);
    }
}
