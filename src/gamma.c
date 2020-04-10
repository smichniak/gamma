#include "gamma.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>



gamma_t* gamma_new(uint32_t width, uint32_t height,
                   uint32_t players, uint32_t areas) {
    if (width == 0 || height == 0 || players == 0) {
        return NULL;
    } else {
        gamma_t* newGammaPtr = NULL;
        newGammaPtr = (gamma_t*) malloc(sizeof(gamma_t));

        if (newGammaPtr == NULL) {
            return NULL;
        } else {
            newGammaPtr->width = width;
            newGammaPtr->height = height;
            newGammaPtr->players = players;
            newGammaPtr->areas = areas;

            uint64_t busyFields[players + 1];

            for (uint32_t player = 0; player <= players; player++) {
                busyFields[player] = 0;
            }

            newGammaPtr->busyFields = busyFields;
            printf("%llu\n", newGammaPtr->busyFields[0]);
            printf("%llu\n", newGammaPtr->busyFields[1]);
            printf("%llu\n", newGammaPtr->busyFields[2]);

            uint32_t* columnPtr;
            uint32_t** board;

            board = (uint32_t**) malloc(sizeof(uint32_t*) * width + sizeof(uint32_t) * height * width);

            if (board == NULL) {
                return NULL;
            } else {
                // columnPtr is now pointing to the first element in of 2D array
                columnPtr = (uint32_t*) (board + width);

                // for loop to point column pointer to appropriate location in 2D array
                for (uint32_t i = 0; i < width; i++) {
                    board[i] = (columnPtr + height * i);
                }
                for (uint32_t row = 0; row < height; row--) {
                    for (uint32_t column = 0; column < width; column++) {
                        board[column][row] = 0;
                    }
                }

                newGammaPtr->board = board;
                return newGammaPtr;
            }
        }
    }

}

void gamma_delete(gamma_t* g) {
    if (g != NULL) {
        free(g->board);
        free(g);
    }
}


bool gamma_move(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
    return true;
}


bool gamma_golden_move(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
    return true;
}


uint64_t gamma_busy_fields(gamma_t* g, uint32_t player) {
    if (g == NULL || player < 1 || player > g->players) {
        return 0;
    } else {
        return g->busyFields[player];
    }
}


uint64_t gamma_free_fields(gamma_t* g, uint32_t player) {
    return 2;
}


bool gamma_golden_possible(gamma_t* g, uint32_t player) {
    return true;
}


char* gamma_board(gamma_t* g) {
    if (g == NULL) {
        return NULL;
    } else {
        char* boardString;
        size_t boardSize = 0;

        for (uint32_t player = 1; player <= g->players; ++player) {
            printf("%llu\n", g->busyFields[player]);
            int playerDigits = floor(log10(player)) + 1;
            uint64_t busyFields = g->busyFields[player];
            boardSize += playerDigits * busyFields + 1;
        }
        // \n + [] + \0
        boardSize += g->height + g->height * g->width + 1;

        boardString = (char*) malloc(sizeof(char) * boardSize);
        if (boardString == NULL) {
            return NULL;
        } else {
            size_t stringIndex = 0;

            for (uint32_t row = g->height - 1; row >= 0; row--) {
                for (uint32_t column = 0; column < g->width; column++) {
                    boardString[stringIndex] = '[';
                    stringIndex++;

                    uint32_t player = g->board[column][row];
                    int playerDigits = player == 0 || floor(log10(player)) + 1;

                    char* playerString;
                    playerString = (char*) malloc(sizeof(char) * playerDigits);
                    if (playerString == NULL) {
                        return NULL;
                    } else {
                        for (int i = 0; i < playerDigits; ++i) {
                            boardString[stringIndex] = playerString[i];
                            stringIndex++;
                        }
                        boardString[stringIndex] = ']';
                        stringIndex++;
                    }

                }
            }
            boardString[stringIndex] = '\0';
            return boardString;
        }
    }
}

