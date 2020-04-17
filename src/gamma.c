/** @file
 * Implementacja modułu gamma.h
 *
 * @author Szymon Michniak <s.michniak@student.uw.edu.pl>
 * @date 16.04.2020
 */

#include "gamma.h"
#include "findUnion.h"
#include <string.h>

/** @struct gamma
 * Struktura przechowująca stan gry.
 */
struct gamma {
    uint32_t width; ///< Szerokość planszy, liczba dodatnia
    uint32_t height; ///< Wysokość planszy, liczba dodatnia
    uint32_t players; ///< Liczba graczy, liczba dodatnia
    uint32_t areas; ///< Maksymalna liczba obszarów, jakie może zająć jeden gracz, liczba dodatnia
    uint64_t freeFields; ///< Wolne pola na planszy, liczba nieujemna
    uint64_t* busyFields; ///< Tablica liczby pól zajętych przez danego gracza, indeksowana numerami graczy
    uint64_t* freeAdjacentFields; ///< Tablica wolnych pól wokół danego gracza, indeksowana numerami graczy
    uint32_t* playerAreas; ///< Tablica zajętych obszarów przez danego gracza, indeksowana numerami graczy
    bool* goldenMoves; ///< Tablica wartości logicznych, @p false dla gracza, który jeszcze nie wykonał złotego ruchu, @p true w przeciwnym przyapdku, indeksowana numerami graczy
    findUnionNode_t*** board; ///< Dwuwymiarowa tablica planszy, w każdym zajętym polu wskaźnik na wierzchołek drzewa Find-Union obszaru, indeksowana współrzędnymi pola
};

/** @brief Sprawdza poprawność współrzędnych.
 * Sprawdza, czy współrzędne @p x i @p y są poprawne dla planszy @p g.
 * @param[in] g       – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] x       – numer kolumny, liczba nieujemna mniejsza od wartości
 *                      @p width z funkcji @ref gamma_new,
 * @param[in] y       – numer wiersza, liczba nieujemna mniejsza od wartości
 *                      @p height z funkcji @ref gamma_new.
 * @return Wartość @p true, dla poprawnych współrzędnych, a @p false
 * w przeciwnym przypadku.
 */
bool validCoordinates(gamma_t* g, uint32_t x, uint32_t y) {
    return x < g->width && y < g->height;
}
/** @brief Sprawdza poprawność współrzędnych.
 * Sprawdza, czy gracz @p player jest poprawny dla planszy @p g.
 * @param[in] g       – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] player  – numer gracza, liczba dodatnia niewiększa od wartości
 *                      @p players z funkcji @ref gamma_new.
 * @return Wartość @p true, dla poprawnego gracza, a @p false
 * w przeciwnym przypadku.
 */
bool validPlayer(gamma_t* g, uint32_t player) {
    return player >= 1 && player <= g->players;
}

gamma_t* gamma_new(uint32_t width, uint32_t height, uint32_t players, uint32_t areas) {
    if (width < 1 || height < 1 || players < 1 || areas < 1) {
        return NULL;
    }
    gamma_t* newGammaPtr = malloc(sizeof(gamma_t));
    if (!newGammaPtr) {
        return NULL;
    }

    newGammaPtr->width = width;
    newGammaPtr->height = height;
    newGammaPtr->players = players;
    newGammaPtr->areas = areas;
    newGammaPtr->freeFields = width * height;

    uint64_t* busyFields = calloc((uint64_t) players + 1, sizeof(uint64_t));
    uint64_t* freeAdjacentFields = calloc((uint64_t) players + 1, sizeof(uint64_t));
    uint32_t* playerAreas = calloc((uint64_t) players + 1, sizeof(uint32_t));
    bool* goldenMoves = calloc((uint64_t) players + 1, sizeof(bool));
    findUnionNode_t*** board = calloc((uint64_t) width * ((uint64_t) height + 1), sizeof(findUnionNode_t*));

    if (!busyFields || !freeAdjacentFields || !playerAreas || !goldenMoves || !board) {
        return NULL;
    }
    newGammaPtr->busyFields = busyFields;
    newGammaPtr->freeAdjacentFields = freeAdjacentFields;
    newGammaPtr->playerAreas = playerAreas;
    newGammaPtr->goldenMoves = goldenMoves;

    // columnPtr is now pointing to the first element in of 2D array
    findUnionNode_t** columnPtr = (findUnionNode_t**) (board + width);

    // for loop to point column pointer to appropriate location in 2D array
    for (uint32_t i = 0; i < width; ++i) {
        board[i] = (columnPtr + height * i);
    }
    newGammaPtr->board = board;
    return newGammaPtr;
}

void gamma_delete(gamma_t* g) {
    if (g) {
        for (uint32_t x = 0; x < g->width; ++x) {
            for (uint32_t y = 0; y < g->height; ++y) {
                free(g->board[x][y]);
            }
        }
        free(g->busyFields);
        free(g->freeAdjacentFields);
        free(g->playerAreas);
        free(g->goldenMoves);
        free(g->board);
        free(g);
    }
}

/** @brief Zwraca pola sąsiednie do danego.
 * Zwraca tablicę par ze współrzędnymi sąsiednich pól.
 * @param[in] g       – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] x       – numer kolumny, liczba nieujemna mniejsza od wartości
 *                      @p width z funkcji @ref gamma_new,
 * @param[in] y       – numer wiersza, liczba nieujemna mniejsza od wartości
 *                      @p height z funkcji @ref gamma_new.
 * @return Wskaźnik na pierwszy element tablicy lub NULL, gdy nie udało się
 * zaalokować pamięci.
 */
Tuple* getAdjacent(gamma_t* g, uint32_t x, uint32_t y) {
    Tuple* adjacent;
    adjacent = calloc(4, sizeof(Tuple));
    if (!adjacent) {
        return NULL;
    }
    int index = 0;

    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if ((dx + dy) % 2 != 0) {
                if (validCoordinates(g, x + dx, y + dy)) {
                    adjacent[index] = createTuple(x + dx, y + dy);
                } else {
                    //Field out of bound
                    adjacent[index] = createTuple(UINT32_MAX, UINT32_MAX);
                }
                index++;
            }
        }
    }
    return adjacent;
}

/** @brief Zwraca liczbę sąsiednich pól z danym graczem.
 * Przegląda tablicę pól @p adjacent i zlicza te, które mają w sobie gracza @p player.
 * @param[in] g       – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] player  – numer gracza, liczba dodatnia niewiększa od wartości
 *                      @p players z funkcji @ref gamma_new,
 * @param[in] adjacent - maksymalnie czteroelementowa tablica par współrzędnych @p x i @p y
 * @return Liczba ze zbioru {0, 1, 2, 3, 4}, liczba sąsiednich pól z danym graczem.
 */
int adjacentWithPLayer(gamma_t* g, uint32_t player, Tuple* adjacent) {
    int samePlayerAdjacent = 0;
    for (int i = 0; i < 4; ++i) {
        uint32_t x2 = adjacent[i].x;
        uint32_t y2 = adjacent[i].y;
        samePlayerAdjacent +=
                validCoordinates(g, x2, y2) && getPlayer(g->board[x2][y2]) == player;
    }
    return samePlayerAdjacent;
}

/** @brief Zwraca liczbę nowych, pustych sąsiednich pól.
 * Przegląda tablicę pól @p adjacent i zlicza puste pola, które nie sąsiadują
 * z zajętym polem z podanym graczem.
 * @param[in] g       – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] player  – numer gracza, liczba dodatnia niewiększa od wartości
 *                      @p players z funkcji @ref gamma_new,
 * @param[in] adjacent - maksymalnie czteroelementowa tablica par współrzędnych @p x i @p y
 * @return Liczba ze zbioru {0, 1, 2, 3, 4}, liczba sąsiednich pól z danym graczem.
 */
int newFreeAdjacent(gamma_t* g, uint32_t player, Tuple* adjacent) {
    int freeAdjacent = 0;
    for (int i = 0; i < 4; ++i) {
        uint32_t x2 = adjacent[i].x;
        uint32_t y2 = adjacent[i].y;
        if (validCoordinates(g, x2, y2) && !g->board[x2][y2]) {
            freeAdjacent++;
            Tuple* adjacentTo2 = getAdjacent(g, x2, y2);
            if (!adjacentTo2) {
                return -1;
            }
            if (adjacentWithPLayer(g, player, adjacentTo2)) {
                freeAdjacent--;
            }
            free(adjacentTo2);
        }
    }
    return freeAdjacent;
}

/** @brief Zwraca liczbę nowych obszarów po zwykłym ruchu.
 * Przegląda tablicę pól @p adjacent i zlicza pola zajęte przez gracza @p player,
 * które po położeniu pionka łączą się w jeden obszar.
 * @param[in, out] g           – wskaźnik na strukturę przechowującą stan gry,
 * @param[in, out] field  – pole, na którym stawiamy pionek, element @p g,
 * @param[in, out] adjacent    - maksymalnie czteroelementowa tablica par współrzędnych @p x i @p y
 * @return Liczba ze zbioru {-3, -2, -1, 0, 1}, o ile zmienia się liczba obszarów zajętych przez gracza.
 */
int newAreasMove(gamma_t* g, findUnionNode_t* field, Tuple* adjacent) {
    int newArea = 1;
    for (int i = 0; i < 4; ++i) {
        uint32_t x2 = adjacent[i].x;
        uint32_t y2 = adjacent[i].y;
        if (validCoordinates(g, x2, y2) && getPlayer(g->board[x2][y2]) == getPlayer(field) &&
            !connected(field, g->board[x2][y2])) {

            unite(field, g->board[x2][y2]);
            newArea--;
        }
    }
    return newArea;
}

/** @brief Aktualizuje liczbę wolnych pól.
 * Przegląda tablicę pól @p adjacent i dla każdego pola aktualizuje liczbę wolnych pół, wokoł tego pola.
 * Każdego gracza zliczamy tylko raz. Przy położeniu nowego pionka zmniejszamy liczbę wolnych pól o 1, a
 * gdy usuwamy pionek, zwiększamy.
 * @param[in, out] g           – wskaźnik na strukturę przechowującą stan gry,
 * @param[in, out] adjacent    - maksymalnie czteroelementowa tablica par współrzędnych @p x i @p y
 * @param[in] toAdd            - @p -1 lub @p 1
 */
void updateAdjacentFree(gamma_t* g, Tuple* adjacent, int toAdd) {
    uint32_t alreadyCounted[4] = {0, 0, 0, 0};
    for (int i = 0; i < 4; ++i) {
        uint32_t x2 = adjacent[i].x;
        uint32_t y2 = adjacent[i].y;
        if (validCoordinates(g, x2, y2)) {
            bool counted = false;
            for (int j = 0; j < i; ++j) {
                counted = counted || getPlayer(g->board[x2][y2]) == alreadyCounted[j];
            }
            if (g->board[x2][y2] && !counted) {
                g->freeAdjacentFields[getPlayer(g->board[x2][y2])] += toAdd;
                alreadyCounted[i] = getPlayer(g->board[x2][y2]);
            }
        }
    }
}

bool gamma_move(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
    if (!g || !validPlayer(g, player) || !validCoordinates(g, x, y) || g->board[x][y]) {
        return false;
    }
    Tuple* adjacent = getAdjacent(g, x, y);
    findUnionNode_t* field = makeSet(player);
    if (!adjacent || !field) {
        return false;
    }

    int freeAdjacent = newFreeAdjacent(g, player, adjacent);
    int samePlayerAdjacent = adjacentWithPLayer(g, player, adjacent);
    if (freeAdjacent < 0 || (g->playerAreas[player] == g->areas && !samePlayerAdjacent)) {
        free(adjacent);
        free(field);
        return false;
    }

    updateAdjacentFree(g, adjacent, -1);

    g->busyFields[player]++;
    g->playerAreas[player] += newAreasMove(g, field, adjacent);
    g->freeAdjacentFields[player] += freeAdjacent;
    g->board[x][y] = field;
    g->freeFields--;

    free(adjacent);
    return true;
}

/** @brief Wykonuje algorytm dfs na polach połączonych z polem wejściowym
 * Po usunięciu pionka przechodzi pola połączone z nim i umieszcza w nich nowe wskaźniki na wierzchołki
 * Find-Union, które nie są połączone z usuniętym pionkiem. Stare pola do zwolnienia później umieszcza
 * w tablicy, na którą wskazuje @p oldFields.
 * @param[in,out] g   – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] x       – numer kolumny, liczba nieujemna mniejsza od wartości
 *                      @p width z funkcji @ref gamma_new,
 * @param[in] y       – numer wiersza, liczba nieujemna mniejsza od wartości
 *                      @p height z funkcji @ref gamma_new,
 * @param[in, out] oldFields - wskaźnik na pierwszy element tablicy wskaźników na pola,
 * @param[in, out] oldFieldsIndexPtr - wskaźnik na indeks pierwszego wolnego miejsca w tablicy
 * @p oldFields.
 * @return Wartość @p true, jeśli pomyślnie wykonano dfs dla wszytskich potrzebnych pól, @p false
 * w przypadku problemów z pamięcią.
 */
bool dfs(gamma_t* g, uint32_t x, uint32_t y, findUnionNode_t** oldFields, uint64_t* oldFieldsIndexPtr) {
    if (!g->board[x][y]) {
        return true;
    }
    uint32_t player = getPlayer(g->board[x][y]);
    stackNode_t* stackPtr = createStack(x, y);

    if (!stackPtr) {
        return false;
    }

    while (!isStackEmpty(stackPtr)) {
        uint32_t currentX = getLast(stackPtr).x;
        uint32_t currentY = getLast(stackPtr).y;
        stackPtr = removeLast(stackPtr);

        Tuple* adjacent = getAdjacent(g, currentX, currentY);
        if (!adjacent) {
            removeStack(stackPtr);
            return false;
        }

        findUnionNode_t* newField = makeSet(player);
        if (!newField) {
            return false;
        }

        oldFields[*oldFieldsIndexPtr] = g->board[currentX][currentY];
        (*oldFieldsIndexPtr)++;
        g->board[currentX][currentY] = newField;
        unite(g->board[x][y], newField);

        for (int i = 0; i < 4; ++i) {
            uint32_t x2 = adjacent[i].x;
            uint32_t y2 = adjacent[i].y;
            if (validCoordinates(g, x2, y2) && getPlayer(g->board[x2][y2]) == player &&
                !connected(g->board[x][y], g->board[x2][y2])) {
                stackNode_t* newLast = putLast(stackPtr, x2, y2);
                if (!newLast) {
                    removeStack(stackPtr);
                    free(adjacent);
                    return false;
                }
                stackPtr = newLast;
            }
        }
        free(adjacent);
    }
    return true;
}

/** @brief Uruchamia algorytm dfs dla sąsiednich pól.
 * Przegląda tablicę pól @p adjacent i uruchami funkcję @ref dfs dla każdego z nich.
 * @param[in,out] g   – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] busyPlayer  – numer gracza na usuwanym polu, liczba dodatnia niewiększa
 *                          od wartości @p players z funkcji @ref gamma_new,
 * @param[in, out] adjacent - maksymalnie czteroelementowa tablica par współrzędnych @p x i @p y
 * @param[in, out] oldFields - wskaźnik na pierwszy element tablicy wskaźników na pola,
 * @param[in, out] oldFieldsIndexPtr - wskaźnik na indeks pierwszego wolnego miejsca w tablicy
 * @p oldFields.
 * @return Wartość @p true, jeśli pomyślnie wykonano dfs dla wszytskich sąsiednich pól, @p false
 * w przypadku problemów z pamięcią.
 */
bool dfsOnAdjacent(gamma_t* g, uint32_t busyPlayer, Tuple* adjacent, findUnionNode_t** oldFields,
                   uint64_t* oldFieldsIndexPtr) {
    for (int i = 0; i < 4; ++i) {
        uint32_t x2 = adjacent[i].x;
        uint32_t y2 = adjacent[i].y;
        if (validCoordinates(g, x2, y2) && getPlayer(g->board[x2][y2]) == busyPlayer) {
            bool alreadyDoneDfs = false;
            for (int j = 0; j < i; ++j) {
                uint32_t xj = adjacent[j].x;
                uint32_t yj = adjacent[j].y;
                alreadyDoneDfs = alreadyDoneDfs || (validCoordinates(g, xj, yj) &&
                                                    connected(g->board[x2][y2], g->board[xj][yj]));
            }
            if (!alreadyDoneDfs) {
                bool successfulDfs = dfs(g, x2, y2, oldFields, oldFieldsIndexPtr);
                if (!successfulDfs) {
                    free(adjacent);
                    for (uint64_t field = 0; field < *oldFieldsIndexPtr; ++field) {
                        free(oldFields[field]);
                    }
                    free(oldFields);
                    return false;
                }
            }
        }
    }

    return true;
}

bool gamma_golden_move(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
    if (!g || !validPlayer(g, player) || !validCoordinates(g, x, y) || g->goldenMoves[player] ||
        !g->board[x][y] || getPlayer(g->board[x][y]) == player) {
        return false;
    }
    Tuple* adjacent = getAdjacent(g, x, y);
    if (!adjacent) {
        return false;
    }

    if (g->playerAreas[player] == g->areas && !adjacentWithPLayer(g, player, adjacent)) {
        free(adjacent);
        return false;
    }

    findUnionNode_t** oldFields = malloc(2 * g->height * g->width * sizeof(findUnionNode_t*));
    if (!oldFields) {
        free(adjacent);
        return false;
    }
    uint64_t oldFieldsIndex = 1;
    uint64_t* oldFieldsIndexPtr = &oldFieldsIndex;

    uint32_t busyPlayer = getPlayer(g->board[x][y]);
    oldFields[0] = g->board[x][y];
    g->board[x][y] = NULL;

    bool successfulDfs = dfsOnAdjacent(g, busyPlayer, adjacent, oldFields, oldFieldsIndexPtr);
    if (!successfulDfs) {
        free(adjacent);
        return false;
    }

    updateAdjacentFree(g, adjacent, 1);

    int newAreas = adjacentWithPLayer(g, busyPlayer, adjacent) - 1;
    for (int i = 0; i < 4; ++i) {
        uint32_t xi = adjacent[i].x;
        uint32_t yi = adjacent[i].y;
        if (validCoordinates(g, xi, yi) && getPlayer(g->board[xi][yi]) == busyPlayer) {
            for (int j = i + 1; j < 4; ++j) {
                uint32_t xj = adjacent[j].x;
                uint32_t yj = adjacent[j].y;
                if (validCoordinates(g, xj, yj) &&
                    getPlayer(g->board[xj][yj]) == busyPlayer &&
                    connected(g->board[xi][yi], g->board[xj][yj])) {
                    newAreas--;
                    for (int k = j + 1; k < 4; ++k) {
                        uint32_t xk = adjacent[k].x;
                        uint32_t yk = adjacent[k].y;
                        if (validCoordinates(g, xk, yk) && g->board[xk][yk] &&
                            connected(g->board[xj][yj], g->board[xk][yk])) {
                            newAreas++;
                            if (k == 2) {
                                uint32_t x3 = adjacent[3].x;
                                uint32_t y3 = adjacent[3].y;
                                if (validCoordinates(g, x3, y3) && g->board[x3][y3] &&
                                    connected(g->board[xk][yk], g->board[x3][y3])) {
                                    newAreas--;
                                }
                            }
                        }
                    }
                }
            }
        }
    }


    int freeAdjacentFields = newFreeAdjacent(g, busyPlayer, adjacent);
    if (freeAdjacentFields < 0) {
        free(adjacent);
        return false;
    }
    free(adjacent);
    for (uint64_t field = 0; field < oldFieldsIndex; ++field) {
        free(oldFields[field]);
    }
    free(oldFields);

    g->freeAdjacentFields[busyPlayer] -= freeAdjacentFields;
    g->freeFields++;
    g->busyFields[busyPlayer]--;
    g->playerAreas[busyPlayer] += newAreas;

    if (g->playerAreas[busyPlayer] > g->areas) {

        gamma_move(g, busyPlayer, x, y);
        return false;
    }

    g->goldenMoves[player] = true;
    gamma_move(g, player, x, y);
    return true;

}

uint64_t gamma_busy_fields(gamma_t* g, uint32_t player) {
    if (!g || !validPlayer(g, player)) {
        return 0;
    } else {
        return g->busyFields[player];
    }
}

uint64_t gamma_free_fields(gamma_t* g, uint32_t player) {
    if (!g || !validPlayer(g, player)) {
        return 0;
    }
    if (g->playerAreas[player] == g->areas) {
        return g->freeAdjacentFields[player];
    }
    return g->freeFields;
}

bool gamma_golden_possible(gamma_t* g, uint32_t player) {
    if (!g || !validPlayer(g, player) || g->goldenMoves[player]) {
        return false;
    }
    for (uint32_t otherPlayer = g->players; otherPlayer > 0; --otherPlayer) {
        if (g->busyFields[otherPlayer] > 0 && player != otherPlayer) {
            return true;
        }
    }
    return false;
}

/** @brief Zwraca największego gracza na planszy.
 * Przeszukuje tablice zajętych pól i zwraca największego gracza z niezerową liczbą zajętych pól.
 * @param[in] g       – wskaźnik na strukturę przechowującą stan gry.
 * @return Numer największego gracza, który ma pionek na planszy.
 */
uint32_t maxPlayerOnBoard(gamma_t* g) {
    for (uint32_t player = g->players; player > 0; --player) {
        if (g->busyFields[player] > 0) {
            return player;
        }
    }
    return 0;
}

/** @brief Dodaje gracza do napisu planszy.
 * Dodaje numer gracza jako napis na końcu tablicy znaków reprezentującej planszę, napis gracza uzupełnia
 * pustymi znakami, by miał taką długość, jak długość napisu największego gracza na planszy.
 * @param[in] player  – numer gracza, liczba dodatnia niewiększa od wartości
 *                      @p players z funkcji @ref gamma_new,
 * @param[in] maxPlayerDigits - liczba cyfr największego gracza,
 * @param[in, out] stringIndex - indeks ostatniego wolnego miejsca w tablicy znaków,
 * @param[in, out] boardString - tablica znaków, napis reprezentujący planszę.
 * @return Numer największego gracza, który ma pionek na planszy.
 */
size_t addToBoard(uint32_t player, int maxPlayerDigits, size_t stringIndex, char* boardString) {
    int playerDigits = digits(player);

    char* playerString;
    //+1 for \0
    playerString = malloc(sizeof(char) * (playerDigits + 1));
    if (!playerString) {
        return 0;
    }

    player == 0 ? playerString[0] = '.' : sprintf(playerString, "%u", player);

    for (int digitIndex = 0; digitIndex < playerDigits; ++digitIndex) {
        boardString[stringIndex] = playerString[digitIndex];
        stringIndex++;
        maxPlayerDigits--;
    }
    for (int spaceIndex = 0; spaceIndex < maxPlayerDigits; ++spaceIndex) {
        boardString[stringIndex] = ' ';
        stringIndex++;
    }

    free(playerString);
    return stringIndex;
}

char* gamma_board(gamma_t* g) {
    if (!g) {
        return NULL;
    }

    uint32_t maxPlayer = maxPlayerOnBoard(g);
    int maxPlayerDigits = digits(maxPlayer);

    uint64_t spaces = maxPlayerDigits == 1 ? 0 : g->width * g->height;

    char* boardString;
    boardString = malloc(
            sizeof(char) * (maxPlayerDigits * g->width * g->height + spaces + g->height + 1));
    if (!boardString) {
        return NULL;
    }

    size_t stringIndex = 0;
    for (uint32_t row = g->height - 1; row < g->height; --row) {
        for (uint32_t column = 0; column < g->width; ++column) {

            findUnionNode_t* fieldPtr = g->board[column][row];
            uint32_t player = getPlayer(fieldPtr);

            stringIndex = addToBoard(player, maxPlayerDigits, stringIndex, boardString);
            if (stringIndex == 0) {
                free(boardString);
                return NULL;
            }

            if (spaces) {
                boardString[stringIndex] = ' ';
                stringIndex++;
            }
        }
        //Add \n after each row
        boardString[stringIndex] = '\n';
        stringIndex++;
    }
    boardString[stringIndex] = '\0';
    return boardString;
}
