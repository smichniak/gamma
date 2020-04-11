#include "gamma.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>


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

            uint64_t* busyFields;
            busyFields = (uint64_t*) calloc((players + 1), sizeof(uint64_t));

            newGammaPtr->busyFields = busyFields;

            uint32_t* columnPtr;
            uint32_t** board;

            board = (uint32_t**) calloc(width * (height + 1), sizeof(uint32_t*));

            if (board == NULL) {
                return NULL;
            } else {
                // columnPtr is now pointing to the first element in of 2D array
                columnPtr = (uint32_t*) (board + width);

                // for loop to point column pointer to appropriate location in 2D array
                for (uint32_t i = 0; i < width; ++i) {
                    board[i] = (columnPtr + height * i);
                }
                newGammaPtr->board = board;
                return newGammaPtr;
            }
        }
    }

}

void gamma_delete(gamma_t* g) {
    if (g != NULL) {
        free(g->busyFields);
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


size_t boardStringSize(gamma_t* g) {
    size_t boardSize = 0;

    // \n + [] + \0
    boardSize += g->height * (1 + g->width);

    for (uint32_t player = 10; player <= g->players; ++player) {
        uint64_t busyFields = g->busyFields[player];
        //Players with more than 2 digits
        int playerDigits = floor(log10(player));
        boardSize += playerDigits * busyFields;
    }

    return boardSize;

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
            char* playerString;

            uint32_t player = g->board[column][row];
            int playerDigits = player == 0 || floor(log10(player)) + 1;

            playerString = (char*) malloc(sizeof(char) * playerDigits);

            if (playerString == NULL) {
                return NULL;
            }

            if (player == 0) {
                playerString[0] = '.';
            } else {
                sprintf(playerString, "%lu", player);
            }

            for (int i = 0; i < playerDigits; ++i) {
                boardString[stringIndex] = playerString[i];
                stringIndex++;
            }

            free(playerString);

        }
        boardString[stringIndex] = '\n';
        stringIndex++;
    }
    return boardString;


}

