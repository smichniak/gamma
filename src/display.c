/** @file
 * Implementacja modułu display.h
 *
 * @author Szymon Michniak <s.michniak@student.uw.edu.pl>
 * @date 16.05.2020
 */

#include <inttypes.h>
#include <string.h>
#include "display.h"

/** Początek kodu, który zmienia podświetlenie tła na białe i tekst na czarny.
 */
const char* BEGIN_HIGHLIGHT = "\033[7m";

/** Koniec kodu podświetlenia.
 */
const char* END_HIGHLIGHT = "\033[m";

/** Łączna liczba znaków w kodach podświetlenia.
 */
const int CODE_LENGTH = 7;

//Zmienna globalna, by można było z niej korzystać w razie potrzeby w changeTerminalToOriginal, które jest
//wywoływana w exitInteractive
/** Struktura przechowująca informacje o ustawieniach terminala.
 */
struct termios original;

void clear() {
    printf("\033[2J");
    printf("\033[H");
}

void changeTerminalToRaw() {
    struct termios raw;

    // Save original serial communication configuration for stdin
    if (tcgetattr(STDIN_FILENO, &original) != 0) {
        exit(1);
    }
    raw = original;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSANOW, &raw) != 0) {
        exit(1);
    }
    //Ukryj kursor
    printf("\e[?25l");
}

void changeTerminalToOriginal() {
    //Pokaż kursor
    printf("\e[?25h");
    if (tcsetattr(STDIN_FILENO, TCSANOW, &original) != 0) {
        exit(1);
    }
}

void exitInteractive(int code) {
    changeTerminalToOriginal();
    if (code == 0) {
        exit(0);
    } else {
        exit(code);
    }
}

/** @brief Zwraca największego gracza na planszy.
 * Przeszukuje tablice zajętych pól i zwraca największego gracza z niezerową liczbą zajętych pól.
 * @param[in] g       – wskaźnik na strukturę przechowującą st
 * an gry.
 * @return Numer największego gracza, który ma pionek na planszy.
 */
static uint32_t maxPlayerOnBoard(gamma_t* g) {
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
static size_t addHighlight(char* boardString, size_t stringIndex, const char* highlight) {
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
static size_t addSpaces(char* boardString, size_t stringIndex, int spaces) {
    for (int spaceIndex = 0; spaceIndex < spaces; ++spaceIndex) {
        //Pozostale znaki uzupełniamy spacjami
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
 * param[in] highlight         - @p true jeśli pole ma być podświetlone, @p false w przeciwnym przypadku
 * @return Indeks ostatniego wolnego miejsca w tablicy znaków, po dodaniu napisu.
 */
static size_t addToBoard(gamma_t* g, uint32_t column, uint32_t row, int maxPlayerDigits, size_t stringIndex,
                         char* boardString, bool highlight) {
    uint32_t player = get_player_on_field(g, column, row);
    int playerDigits = digits(player);

    char* playerString;
    //+1 dla \0
    playerString = calloc(playerDigits + highlight * CODE_LENGTH + 1, sizeof(char));
    if (!playerString) {
        return 0;
    }

    player == 0 ? playerString[0] = '.' : sprintf(playerString, "%u", player);

    if (highlight) {
        stringIndex = addHighlight(boardString, stringIndex, BEGIN_HIGHLIGHT);
    }

    for (int digitIndex = 0; digitIndex < playerDigits; ++digitIndex) {
        boardString[stringIndex] = playerString[digitIndex];
        stringIndex++;
        maxPlayerDigits--;
    }
    if (highlight) {
        stringIndex = addHighlight(boardString, stringIndex, END_HIGHLIGHT);
    }

    stringIndex = addSpaces(boardString, stringIndex, maxPlayerDigits);

    free(playerString);
    return stringIndex;
}

char* boardWithHighlight(gamma_t* g, uint32_t x, uint32_t y) {
    if (!g) {
        return NULL;
    }
    bool highlight = x < UINT32_MAX;
    uint32_t width = get_width(g);
    uint32_t height = get_height(g);

    uint32_t maxPlayer = maxPlayerOnBoard(g);
    int maxPlayerDigits = digits(maxPlayer);

    //Jeśli na planszy są gracze co najmniej dwucyfrowi, to między każdym gracze robię odstęp
    uint64_t spaces = maxPlayerDigits == 1 ? 0 : width * height;

    char* boardString;
    //+height na \n po każdym rzędzie, +1 na \0
    boardString = calloc(
            maxPlayerDigits * (uint64_t) width * (uint64_t) height + spaces + height +
            highlight * CODE_LENGTH + 1, sizeof(char));
    if (!boardString) {
        return NULL;
    }

    size_t stringIndex = 0;
    for (uint32_t row = height - 1; row < height; --row) {
        for (uint32_t column = 0; column < width; ++column) {
            bool highlightField = highlight && column == x && row == y;

            stringIndex = addToBoard(g, column, row, maxPlayerDigits, stringIndex, boardString, highlightField);
            if (stringIndex == 0) {
                free(boardString);
                return NULL;
            }

            stringIndex = addSpaces(boardString, stringIndex, spaces > 0);
        }
        //\n po każdym rzędzie
        boardString[stringIndex] = '\n';
        stringIndex++;
    }
    boardString[stringIndex] = '\0';
    return boardString;
}

void printWithHighlight(gamma_t* g, uint32_t x, uint32_t y, unsigned long long line) {
    char* board = boardWithHighlight(g, x, y);
    if (!board) {
        if (line == 0) {
            exitInteractive(1);
        } else {
            printError(line);
        }
    } else {
        printf("%s", board);
        free(board);
    }
}

void printResults(gamma_t* g) {
    uint32_t players = get_players(g);
    for (uint32_t player = 1; player <= players; ++player) {
        printf("PLAYER %u %" PRIu64 "\n", player, gamma_busy_fields(g, player));
    }
}

void printError(unsigned long long line) {
    fprintf(stderr, "ERROR %llu\n", line);
}

