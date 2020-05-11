#include "display.h"
#include "utilities.h"
#include "findUnion.h"
#include <stdio.h>
#include <string.h>

const char BEGIN_HIGHLIGHT[] = "\033[7m";
const char END_HIGHLIGHT[] = "\033[m";
const int CODE_LENGTH = 8;

void clear() {
    printf("\033[2J");
    printf("\033[H");
    printf("\033[1;1H");
    //  printf("\e[1;1H\e[2J");
}

/** @brief Zwraca największego gracza na planszy.
 * Przeszukuje tablice zajętych pól i zwraca największego gracza z niezerową liczbą zajętych pól.
 * @param[in] g       – wskaźnik na strukturę przechowującą stan gry.
 * @return Numer największego gracza, który ma pionek na planszy.
 */
uint32_t maxPlayerOnBoard(gamma_t* g) {
    for (uint32_t player = get_players(g); player > 0; --player) {
        if (get_busy_fields(g, player) > 0) {
            return player;
        }
    }
    return 0;
}

/** @brief Dodaje gracza do napisu planszy.
 * Dodaje numer gracza jako napis na końcu tablicy znaków reprezentującej planszę, napis gracza uzupełnia
 * pustymi znakami, by miał taką długość, jak długość napisu największego gracza na planszy.
 * @param[in] player           – numer gracza, liczba dodatnia niewiększa od wartości
 *                               @p players z funkcji @ref gamma_new,
 * @param[in] maxPlayerDigits  - liczba cyfr największego gracza,
 * @param[in, out] stringIndex - indeks ostatniego wolnego miejsca w tablicy znaków,
 * @param[in, out] boardString - tablica znaków, napis reprezentujący planszę.
 * @return Numer największego gracza, który ma pionek na planszy.
 */
size_t addToBoard(gamma_t* g, uint32_t column, uint32_t row, int maxPlayerDigits, size_t stringIndex,
                  char* boardString, bool highlight) {
    uint32_t player = getPlayer(get_field(g, column, row));
    int playerDigits = digits(player);

    char* playerString;
    //+1 dla \0
    playerString = malloc(sizeof(char) * (playerDigits + highlight * CODE_LENGTH + 1));
    if (!playerString) {
        return 0;
    }

    player == 0 ? playerString[0] = '.' : sprintf(playerString, "%u", player);

    if (highlight) {
        for (uint32_t k = 0; k < strlen(BEGIN_HIGHLIGHT); ++k) {
            boardString[stringIndex] = BEGIN_HIGHLIGHT[k];
            stringIndex++;
        }
    }

    for (int digitIndex = 0; digitIndex < playerDigits; ++digitIndex) {
        boardString[stringIndex] = playerString[digitIndex];
        stringIndex++;
        maxPlayerDigits--;
    }
    if (highlight) {
        for (uint32_t k = 0; k < strlen(END_HIGHLIGHT); ++k) {
            boardString[stringIndex] = END_HIGHLIGHT[k];
            stringIndex++;
        }
    }

    for (int spaceIndex = 0; spaceIndex < maxPlayerDigits; ++spaceIndex) {
        //Pozostale znaki uzupełniamy spacjami
        boardString[stringIndex] = ' ';
        stringIndex++;
    }

    free(playerString);
    return stringIndex;
}

char* boardWithHighlight(gamma_t* g, bool highlight, uint32_t x, uint32_t y) {
    if (!g) {
        return NULL;
    }
    uint32_t width = get_width(g);
    uint32_t height = get_height(g);

    uint32_t maxPlayer = maxPlayerOnBoard(g);
    int maxPlayerDigits = digits(maxPlayer);

    //Jeśli na planszy są gracze co najmniej dwucyfrowi, to między każdym gracze robię odstęp
    uint64_t spaces = maxPlayerDigits == 1 ? 0 : width * height;

    char* boardString;
    //+height na \n po każdym rzędzie, +1 na \0
    boardString = malloc(sizeof(char) * (maxPlayerDigits * width * height + spaces + height +
                                         highlight * CODE_LENGTH + 1));
    if (!boardString) {
        return NULL;
    }

    size_t stringIndex = 0;
    for (uint32_t row = height - 1; row < height; --row) {
        for (uint32_t column = 0; column < width; ++column) {
            bool highlightField = highlight && x == column && y == row;

            stringIndex = addToBoard(g, column, row, maxPlayerDigits, stringIndex, boardString,
                                     highlightField);
            if (stringIndex == 0) {
                free(boardString);
                return NULL;
            }

            if (spaces) {
                boardString[stringIndex] = ' ';
                stringIndex++;
            }
        }
        //\n po każdym rzędzie
        boardString[stringIndex] = '\n';
        stringIndex++;
    }
    boardString[stringIndex] = '\0';
    return boardString;
}

void printResults(gamma_t* g) {
    uint32_t players = get_players(g);
    for (uint32_t player = 1; player <= players; ++player) {
        printf("PLAYER %u %llu\n", player, get_busy_fields(g, player));
    }


}