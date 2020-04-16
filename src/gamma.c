#include "gamma.h"
#include "findUnion.h"
#include <string.h>


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

    uint64_t* busyFields = calloc((players + 1), sizeof(uint64_t));
    uint64_t* freeAdjacentFields = calloc((players + 1), sizeof(uint64_t));
    uint32_t* playerAreas = calloc((players + 1), sizeof(uint32_t));
    bool* goldenMoves = calloc((players + 1), sizeof(bool));
    findUnionNode_t*** board = calloc(width * (height + 1), sizeof(findUnionNode_t*));

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
                if (x + dx < g->width && y + dy < g->height) {
                    adjacent[index] = createTuple(x + dx, y + dy);
                } else {
                    //Field out of bound
                    adjacent[index] = createTuple(MAX_INT32, MAX_INT32);
                }
                index++;
            }
        }
    }
    return adjacent;
}

int adjacentWithPLayer(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
    int samePlayerAdjacent = 0;
    Tuple* adjacent = getAdjacent(g, x, y);

    for (int i = 0; i < 4; ++i) {
        uint32_t x2 = adjacent[i].x;
        uint32_t y2 = adjacent[i].y;
        samePlayerAdjacent += x2 != MAX_INT32 && g->board[x2][y2] && g->board[x2][y2]->player == player;
    }
    free(adjacent);
    return samePlayerAdjacent;
}

int freeAdjacent(gamma_t* g, uint32_t player, Tuple* adjacent) {
    int freeAdjacentCount = 0;
    for (int i = 0; i < 4; ++i) {
        uint32_t x2 = adjacent[i].x;
        uint32_t y2 = adjacent[i].y;
        if (x2 != MAX_INT32 && !g->board[x2][y2]) {
            freeAdjacentCount++;
            if (adjacentWithPLayer(g, player, x2, y2)) {
                freeAdjacentCount--;
            }

        }
    }
    return freeAdjacentCount;
}


bool gamma_move(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
    if (!g || player < 1 || player > g->players || x >= g->width || y >= g->height ||
        g->board[x][y] ||
        (g->playerAreas[player] == g->areas && !adjacentWithPLayer(g, player, x, y))) {
        return false;
    }

    bool samePlayerAdjacent = false;

    uint32_t alreadyCounted[4] = {0, 0, 0, 0};

    Tuple* adjacent = getAdjacent(g, x, y);
    if (!adjacent) {
        return false;
    }

    int freeAdjacentFields = freeAdjacent(g, player, adjacent);

    findUnionNode_t* field = makeSet(player);
    if (!field) {
        return false;
    }

    int newArea = 1;
    for (int i = 0; i < 4; ++i) {
        uint32_t x2 = adjacent[i].x;
        uint32_t y2 = adjacent[i].y;
        if (x2 != MAX_INT32 && g->board[x2][y2]) {
            if (g->board[x2][y2]->player == player) {
                if (!connected(field, g->board[x2][y2])) {
                    unite(field, g->board[x2][y2]);
                    newArea--;
                    samePlayerAdjacent = true;
                }
            } else if (alreadyCounted[0] != g->board[x2][y2]->player &&
                       alreadyCounted[1] != g->board[x2][y2]->player &&
                       alreadyCounted[2] != g->board[x2][y2]->player &&
                       alreadyCounted[3] != g->board[x2][y2]->player) {

                g->freeAdjacentFields[g->board[x2][y2]->player]--;
                alreadyCounted[i] = g->board[x2][y2]->player;
            }
        }
    }
    free(adjacent);

    g->busyFields[player]++;
    g->playerAreas[player] += newArea;
    g->freeAdjacentFields[player] += freeAdjacentFields - samePlayerAdjacent;
    g->board[x][y] = field;
    g->freeFields--;

    return true;
}

bool dfs(gamma_t* g, uint32_t x, uint32_t y, findUnionNode_t** roots, int* rootIndexPtr) {
    if (!g->board[x][y]) {
        return true;
    }
    uint32_t player = g->board[x][y]->player;

    StackNode_t* stackPtr = createStack(x, y);

    if (!stackPtr) {
        return false;
    }

    while (!isStackEmpty(stackPtr)) {
        uint32_t currentX = getLast(stackPtr).x;
        uint32_t currentY = getLast(stackPtr).y;
        stackPtr = removeLast(stackPtr);

        Tuple* adjacent = getAdjacent(g, currentX, currentY);
        if (!adjacent) {
            return false;
        }

        roots[*rootIndexPtr] = g->board[currentX][currentY];
        (*rootIndexPtr)++;


        findUnionNode_t* field = makeSet(player);
        if (!field) {
            return false;
        }

        g->board[currentX][currentY] = field;
        unite(g->board[x][y], field);

        for (int i = 0; i < 4; ++i) {
            uint32_t x2 = adjacent[i].x;
            uint32_t y2 = adjacent[i].y;
            if (x2 != MAX_INT32 && g->board[x2][y2] && g->board[x2][y2]->player == player &&
                !connected(g->board[x][y], g->board[x2][y2])) {
                StackNode_t* newLast = putLast(stackPtr, x2, y2);
                if (!newLast) {
                    removeStack(stackPtr);
                    return false;
                }
                stackPtr = newLast;
            }
        }
        free(adjacent);

    }
    return true;
}

bool fixArea(gamma_t* g, uint32_t x, uint32_t y, findUnionNode_t** roots, int* rootIndexPtr) {
    dfs(g, x, y, roots, rootIndexPtr);
    return true;
}


bool gamma_golden_move(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
    if (!g || player < 1 || player > g->players || x >= g->width || y >= g->height || g->goldenMoves[player] ||
        !g->board[x][y] || g->board[x][y]->player == player ||
        (g->playerAreas[player] == g->areas && !adjacentWithPLayer(g, player, x, y))) {
        return false;
    }

    findUnionNode_t** roots = calloc(g->height * g->width, sizeof(findUnionNode_t*));
    if (!roots) {
        return false;
    }
    int rootsIndex = 0;
    int* rootsIndexPtr = &rootsIndex;


    uint32_t busyPlayer = g->board[x][y]->player;
    Tuple* adjacent = getAdjacent(g, x, y);
    int newAreas = adjacentWithPLayer(g, busyPlayer, x, y) - 1;

    if (!adjacent) {
        return false;
    }

    g->board[x][y]->player = 0;

    g->freeFields++;
    g->busyFields[busyPlayer]--;


    for (int i = 0; i < 4; ++i) {
        uint32_t x2 = adjacent[i].x;
        uint32_t y2 = adjacent[i].y;
        if (x2 != MAX_INT32 && g->board[x2][y2] && g->board[x2][y2]->player == busyPlayer) {
            //TODO
            //Check for memory errors
            fixArea(g, x2, y2, roots, rootsIndexPtr);

        }
    }


    uint32_t alreadyCounted[4] = {0, 0, 0, 0};

    //TODO
    //Count new areas for adajacent players, not the old one



    for (int i = 0; i < 4; ++i) {
        uint32_t xi = adjacent[i].x;
        uint32_t yi = adjacent[i].y;
        if (xi != MAX_INT32 && g->board[xi][yi]) {
            bool adjacentAlreadyCounted = false;
            for (int l = 0; l < 3; ++l) {
                adjacentAlreadyCounted =
                        adjacentAlreadyCounted || alreadyCounted[l] == g->board[xi][yi]->player;
            }
            if (!adjacentAlreadyCounted) {
                alreadyCounted[i] = g->board[xi][yi]->player;
                g->freeAdjacentFields[alreadyCounted[i]]++;
            }

            for (int j = i + 1; j < 4; ++j) {

                uint32_t xj = adjacent[j].x;
                uint32_t yj = adjacent[j].y;
                if (xj != MAX_INT32 && g->board[xj][yj] && g->board[xj][yj]->player == busyPlayer &&
                    connected(g->board[xi][yi], g->board[xj][yj])) {
                    newAreas--;
                    for (int k = j + 1; k < 4; ++k) {
                        uint32_t xk = adjacent[k].x;
                        uint32_t yk = adjacent[k].y;
                        if (xk != MAX_INT32 && g->board[xk][yk] &&
                            connected(g->board[xj][yj], g->board[xk][yk])) {
                            newAreas++;
                            if (i == 0 && j == 1 && k == 2) {
                                uint32_t x3 = adjacent[3].x;
                                uint32_t y3 = adjacent[3].y;
                                if (x3 != MAX_INT32 && g->board[x3][y3] &&
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


    free(g->board[x][y]);
    g->board[x][y] = NULL;


    g->playerAreas[busyPlayer] += newAreas;
    int freeAdjacentFields = freeAdjacent(g, busyPlayer, adjacent);
    g->freeAdjacentFields[busyPlayer] -= freeAdjacentFields;
    free(adjacent);

    for (int m = 0; m < rootsIndex; ++m) {
        free(roots[m]);
    }
    free(roots);

    if (g->playerAreas[busyPlayer] > g->areas) {
        gamma_move(g, busyPlayer, x, y);
        return false;
    } else {
        //TODO
        //Memoery errors
        g->goldenMoves[player] = true;

        gamma_move(g, player, x, y);
        return true;
    }


}

uint64_t gamma_busy_fields(gamma_t* g, uint32_t player) {
    if (!g || player < 1 || player > g->players) {
        return 0;
    } else {
        return g->busyFields[player];
    }
}

uint64_t gamma_free_fields(gamma_t* g, uint32_t player) {
    if (!g || player < 1 || player > g->players) {
        return 0;
    }
    if (g->playerAreas[player] == g->areas) {
        return g->freeAdjacentFields[player];
    }
    return g->freeFields;
}

bool gamma_golden_possible(gamma_t* g, uint32_t player) {
    if (!g || player < 1 || player > g->players || g->goldenMoves[player]) {
        return false;
    }
    for (uint32_t otherPlayer = g->players; otherPlayer > 0; --otherPlayer) {
        if (g->busyFields[otherPlayer] > 0 && player != otherPlayer) {
            return true;
        }
    }
    return false;
}

uint32_t maxPlayerOnBoard(gamma_t* g) {
    for (uint32_t player = g->players; player > 0; --player) {
        if (g->busyFields[player] > 0) {
            return player;
        }
    }
    return 0;
}

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
            uint32_t player = fieldPtr ? fieldPtr->player : 0;

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
