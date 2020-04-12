#include "gamma.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

const uint32_t MAX_INT32 = 4294967295;

gamma_t* gamma_new(uint32_t width, uint32_t height,
                   uint32_t players, uint32_t areas) {
    if (width < 1 || height < 1 || players < 1 || areas < 1) {
        return NULL;
    }
    gamma_t* newGammaPtr;
    newGammaPtr = (gamma_t*) malloc(sizeof(gamma_t));

    if (!newGammaPtr) {
        return NULL;
    }
    newGammaPtr->width = width;
    newGammaPtr->height = height;
    newGammaPtr->players = players;
    newGammaPtr->areas = areas;
    newGammaPtr->freeFields = width * height;

    uint64_t* busyFields;
    busyFields = (uint64_t*) calloc((players + 1), sizeof(uint64_t));

    uint64_t* freeAdjacentFields;
    freeAdjacentFields = (uint64_t*) calloc((players + 1), sizeof(uint64_t));

    uint32_t* playerAreas;
    playerAreas = (uint32_t*) calloc((players + 1), sizeof(uint32_t));

    bool* goldenMoves;
    goldenMoves = (bool*) calloc((players + 1), sizeof(bool));

    findUnionNode_t*** board;
    board = (findUnionNode_t***) calloc(width * (height + 1), sizeof(findUnionNode_t*));

    if (busyFields == NULL || freeAdjacentFields == NULL || playerAreas == NULL || goldenMoves == NULL ||
        board == NULL) {
        return NULL;
    }
    newGammaPtr->busyFields = busyFields;
    newGammaPtr->freeAdjacentFields = freeAdjacentFields;
    newGammaPtr->playerAreas = playerAreas;
    newGammaPtr->goldenMoves = goldenMoves;

    findUnionNode_t** columnPtr;
    // columnPtr is now pointing to the first element in of 2D array
    columnPtr = (findUnionNode_t**) (board + width);

    // for loop to point column pointer to appropriate location in 2D array
    for (uint32_t i = 0; i < width; ++i) {
        board[i] = (columnPtr + height * i);
    }
    newGammaPtr->board = board;
    return newGammaPtr;
}

void gamma_delete(gamma_t* g) {
    if (g != NULL) {
        //TODO
        //Free findUnionNodes
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
    adjacent = (Tuple*) calloc(sizeof(Tuple), 4);

    if (adjacent == NULL) {
        return NULL;
    }
    int index = 0;

    for (int dx = -1; dx <= 1; dx += 2) {
        for (int dy = -1; dy <= 1; dy += 2) {
            //TODO
            //Possible error, x + dx possibly < 0
            if (x + dx < g->width && y + dy < g->height) {
                adjacent[index] = createTuple(x + dx, y + dy);
            } else {
                //Field out of bound
                adjacent[index] = createTuple(MAX_INT32, MAX_INT32);
            }
            index++;
        }
    }

    return adjacent;
}

bool samePlayerAdjacent(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
    bool samePlayerAdjacent = false;
    for (int dx = -1; dx <= 1; dx += 2) {
        for (int dy = -1; dy <= 1; dy += 2) {
            //TODO
            //Possible error, x + dx possibly < 0
            samePlayerAdjacent = samePlayerAdjacent ||
                                 (x + dx < g->width && y + dy < g->height && g->board[x + dx][y + dy] != NULL &&
                                  g->board[x + dx][y + dy]->player == player);
        }
    }
    return samePlayerAdjacent;
}


bool gamma_move(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
    if (g == NULL || player < 1 || player > g->players || x >= g->width || y >= g->height || g->board[x][y] != NULL ||
        (g->playerAreas[player] == g->areas && !samePlayerAdjacent(g, player, x, y))) {
        return false;
    }

    int freeAdjacent = 0;
    bool samePLayerAd = false;
    Tuple* adjacent = getAdjacent(g, x, y);
    if (adjacent == NULL) {
        return false;
    }

    findUnionNode_t* field = make_set(player);
    if (field == NULL) {
        return false;
    }

    for (int i = 0; i < 4; ++i) {
        uint32_t x2 = adjacent[i].x;
        uint32_t y2 = adjacent[i].y;
        if (x2 != MAX_INT32) {
            if (g->board[x2][y2] == NULL) {
                freeAdjacent++;
                if (samePlayerAdjacent(g, player, x2, y2)) {
                    freeAdjacent--;
                }
            } else if (g->board[x2][y2]->player == player) {
                merge(field, g->board[x2][y2]);
                samePLayerAd = true;
            }

        }
    }
    free(adjacent);

    if (!samePLayerAd){
        g->playerAreas[player]++;
    }

    g->busyFields[player]++;
    g->freeAdjacentFields += freeAdjacent;
    g->board[x][y] = field;
    g->freeFields--;


    return true;


}

bool gamma_golden_move(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
    if (g == NULL || player < 1 || player > g->players || x >= g->width || y >= g->height || g->goldenMoves[player] ||
        g->board[x][y] == NULL) {
        return false;
    }
}

uint64_t gamma_busy_fields(gamma_t* g, uint32_t player) {
    if (g == NULL || player < 1 || player > g->players) {
        return 0;
    } else {
        return g->busyFields[player];
    }
}

uint64_t gamma_free_fields(gamma_t* g, uint32_t player) {
    if (g == NULL || player < 1 || player > g->players) {
        return 0;
    }
    if (g->playerAreas[player] == g->areas) {
        return g->freeAdjacentFields[player];
    }
    return g->freeFields;
}

bool gamma_golden_possible(gamma_t* g, uint32_t player) {
    if (g == NULL || player < 1 || player > g->players || g->goldenMoves[player]) {
        return false;
    }
    for (uint32_t otherPlayer = 1; otherPlayer <= g->players; ++otherPlayer) {
        if (g->busyFields[otherPlayer] > 0 && player != otherPlayer) {
            return true;
        }
    }
    return false;
}

size_t boardStringSize(gamma_t* g) {
    size_t boardSize = 0;

    // \n + .
    boardSize += g->height * (1 + g->width);

    for (uint32_t player = 10; player <= g->players; ++player) {
        uint64_t busyFields = g->busyFields[player];
        //Players with more than 2 digits
        int playerDigits = floor(log10(player));
        // +2 for []
        boardSize += (playerDigits + 2) * busyFields;
    }

    //+1 for \0
    return boardSize + 1;

}

size_t addToBoard(uint32_t player, size_t stringIndex, char* boardString) {
    if (player == 0) {
        boardString[stringIndex] = '.';
        return stringIndex + 1;
    }
    char* playerString;
    int playerDigits;
    playerDigits = floor(log10(player)) + 1;
    bool oneDigit = playerDigits == 1;

    //+1 for \0
    playerString = (char*) malloc(sizeof(char) * (playerDigits + 1));

    if (playerString == NULL) {
        return 0;
    }

    sprintf(playerString, "%u", player);

    if (!oneDigit) {
        boardString[stringIndex] = '[';
        stringIndex++;
    }

    for (int i = 0; i < playerDigits; ++i) {
        boardString[stringIndex] = playerString[i];
        stringIndex++;
    }

    if (!oneDigit) {
        boardString[stringIndex] = ']';
        stringIndex++;
    }

    free(playerString);
    return stringIndex;
}

char* gamma_board(gamma_t* g) {
    if (g == NULL) {
        return NULL;
    }

    size_t boardSize = boardStringSize(g);

    char* boardString;
    boardString = (char*) malloc(sizeof(char) * boardSize);
    if (boardString == NULL) {
        return NULL;
    }
    size_t stringIndex = 0;

    for (uint32_t row = g->height - 1; row >= 0 && row <= g->height; row--) {
        for (uint32_t column = 0; column < g->width; ++column) {

            uint32_t player;

            findUnionNode_t* fieldPtr = g->board[column][row];
            if (fieldPtr == NULL) {
                player = 0;
            } else {
                player = fieldPtr->player;
            }
            stringIndex = addToBoard(player, stringIndex, boardString);

            if (stringIndex == 0) {
                free(boardString);
                return NULL;
            }
        }
        //Add \n after each row
        boardString[stringIndex] = '\n';
        stringIndex++;
    }

    boardString[stringIndex] = '\0';
    return boardString;
}

