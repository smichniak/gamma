/** @file
 * Implementacja modułu display.h
 *
 * @author Szymon Michniak <s.michniak@student.uw.edu.pl>
 * @date 16.05.2020
 */

#include <inttypes.h>
#include <string.h>
#include "display.h"

static const char* GREEN_TEXT = "\e[0;32m";
static const char* RED_TEXT = "\e[0;31m";
static const char* GREEN_BACKGROUND = "\e[42m";
static const char* RED_BACKGROUND = "\e[41m";
static const char* YELLOW_BACKGROUND = "\e[43m";

/** Koniec kodu podświetlenia.
 */
static const char* END_HIGHLIGHT = "\033[m";

/** Łączna liczba znaków w kodach podświetlenia.
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
 * @param[in, out] boardString - tablica znaków, napis reprezentujący planszę.
 * @param[in, out] stringIndex - indeks ostatniego wolnego miejsca w tablicy znaków,
 * @param[in] highlight        – ANSI escape code, który odpowiada za zmianę koloru tła.
 * @return Indeks ostatniego wolnego miejsca w tablicy znaków, po dodaniu napisu.
 */
static size_t add_highlight(char* boardString, size_t stringIndex, const char* highlight) {
    for (uint32_t k = 0; k < strlen(highlight); ++k) {
        boardString[stringIndex] = highlight[k];
        stringIndex++;
    }
    return stringIndex;
}

/** @brief Dodaje spacje do napisu planszy.
 * Dodaje spacje na końcu tablicy znaków reprezentującej planszę.
 * @param[in, out] boardString - tablica znaków, napis reprezentujący planszę.
 * @param[in, out] stringIndex - indeks ostatniego wolnego miejsca w tablicy znaków,
 * @param[in] spaces           – liczba spacji do dodania.
 * @return Indeks ostatniego wolnego miejsca w tablicy znaków, po dodaniu napisu.
 */
static size_t add_spaces(char* boardString, size_t stringIndex, int spaces) {
    for (int spaceIndex = 0; spaceIndex < spaces; ++spaceIndex) {
        boardString[stringIndex] = ' ';
        stringIndex++;
    }
    return stringIndex;
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
 * @param[in] maxPlayerDigits  - liczba cyfr największego gracza,
 * @param[in, out] stringIndex - indeks ostatniego wolnego miejsca w tablicy znaków,
 * @param[in, out] boardString - tablica znaków, napis reprezentujący planszę.
 * @param[in] highlight         - @p true jeśli pole ma być podświetlone, @p false w przeciwnym przypadku
 * @return Indeks ostatniego wolnego miejsca w tablicy znaków, po dodaniu napisu.
 */
static size_t add_to_board(gamma_t* g, uint32_t column, uint32_t row, int maxPlayerDigits, size_t stringIndex,
                           char* boardString, uint32_t currentPlayer) {
    uint32_t player = get_player_on_field(g, column, row);
    int playerDigits = digits(player);

    char* playerString;
    // +1 dla \0
    playerString = calloc(playerDigits + (currentPlayer > 0) * CODE_LENGTH + 1, sizeof(char));
    if (!playerString) {
        return 0;
    }

    player == 0 ? playerString[0] = '.' : sprintf(playerString, "%u", player);

    if (currentPlayer > 0) {
        if (move_possible(g, currentPlayer, column, row)) {
            stringIndex = add_highlight(boardString, stringIndex, GREEN_BACKGROUND);
        } else if (golden_move_possible(g, currentPlayer, column, row)) {
            stringIndex = add_highlight(boardString, stringIndex, YELLOW_BACKGROUND);
        } else {
            stringIndex = add_highlight(boardString, stringIndex, RED_BACKGROUND);
        }
    }

    // Dodajemy napis numeru gracza
    for (int digitIndex = 0; digitIndex < playerDigits; ++digitIndex) {
        boardString[stringIndex] = playerString[digitIndex];
        stringIndex++;
        maxPlayerDigits--;
    }
    if (currentPlayer > 0) {
        stringIndex = add_highlight(boardString, stringIndex, END_HIGHLIGHT);
    }

    // Pozostale znaki uzupełniamy spacjami
    stringIndex = add_spaces(boardString, stringIndex, maxPlayerDigits);

    free(playerString);
    return stringIndex;
}

char* board_with_highlight(gamma_t* g, uint32_t x, uint32_t y, uint32_t currentPlayer) {
    if (!g) {
        return NULL;
    }
    uint32_t width = get_width(g);
    uint32_t height = get_height(g);

    uint32_t maxPlayer = max_player_on_board(g);
    int maxPlayerDigits = digits(maxPlayer);

    // Jeśli na planszy są gracze co najmniej dwucyfrowi, to między każdym gracze robię odstęp
    uint64_t spaces = maxPlayerDigits == 1 ? 0 : width * height;

    char* boardString;
    // +height na \n po każdym rzędzie, +1 na \0
    boardString = calloc(maxPlayerDigits * (uint64_t) width * (uint64_t) height + spaces + height +
                         (currentPlayer > 0) * CODE_LENGTH + 1, sizeof(char));
    if (!boardString) {
        return NULL;
    }

    size_t stringIndex = 0;
    for (uint32_t row = height - 1; row < height; --row) {
        for (uint32_t column = 0; column < width; ++column) {
            // Decydujemy, czy jesteśmy w polu, które należy podświetlić
            stringIndex = add_to_board(g, column, row, maxPlayerDigits, stringIndex, boardString,
                                       currentPlayer * (column == x && row == y));
            if (stringIndex == 0) {
                free(boardString);
                return NULL;
            }

            stringIndex = add_spaces(boardString, stringIndex, spaces > 0);
        }
        // \n po każdym rzędzie
        boardString[stringIndex] = '\n';
        stringIndex++;
    }
    boardString[stringIndex] = '\0';
    return boardString;
}

void print_with_highlight(gamma_t* g, uint32_t x, uint32_t y, unsigned long long line, uint32_t currentPlayer) {
    char* board = board_with_highlight(g, x, y, currentPlayer);
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
    for (uint32_t player = 1; player <= players; ++player) {
        printf("PLAYER: %u - %" PRIu64 "\n", player, gamma_busy_fields(g, player));
    }
}

inline void print_error(unsigned long long line) {
    fprintf(stderr, "ERROR %llu\n", line);
}

void print_player_info(gamma_t* g, uint32_t player) {
    printf("PLAYER: %u\n", player);
    uint32_t playerAreas = get_player_areas(g, player);
    uint32_t maxAreas = get_areas(g);
    printf("AREAS: ");
    if (playerAreas == maxAreas) {
        printf("%s", RED_TEXT);
    } else {
        printf("%s", GREEN_TEXT);
    }
    printf("%u/%u %s \n", playerAreas, maxAreas, END_HIGHLIGHT);
    printf("OCCUPIED FIELDS: %" PRIu64, gamma_busy_fields(g, player));
    printf("\nFREE FIELDS: %" PRIu64, gamma_free_fields(g, player));
    printf("\nGOLDEN MOVE AVAILABLE: ");
    if (gamma_golden_possible(g, player)) {
        printf("%s true %s \n", GREEN_TEXT, END_HIGHLIGHT);
    } else {
        printf("%s false %s \n", RED_TEXT, END_HIGHLIGHT);
    }
}
