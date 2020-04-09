#include "gamma.h"

typedef struct gamma{
    int x;
} gamma_t;

gamma_t *gamma_new(uint32_t width, uint32_t height,
                   uint32_t players, uint32_t areas) {
    gamma_t gammat;
    gammat.x = 4;
    return &gammat;
}

void gamma_delete(gamma_t *g){

}


bool gamma_move(gamma_t *g, uint32_t player, uint32_t x, uint32_t y){
    return true;
}


bool gamma_golden_move(gamma_t *g, uint32_t player, uint32_t x, uint32_t y){
    return true;
}


uint64_t gamma_busy_fields(gamma_t *g, uint32_t player){
    return 2;
}


uint64_t gamma_free_fields(gamma_t *g, uint32_t player){
    return 2;
}


bool gamma_golden_possible(gamma_t *g, uint32_t player) {
    return true;
}


char *gamma_board(gamma_t *g){
    return "";
}

