/** @file
 * Przykładowe użycie silnika gry gamma
 *
 * @author Marcin Peczarski <marpe@mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 18.03.2020
 */

// CMake w wersji release wyłącza asercje.
#ifdef NDEBUG
#undef NDEBUG
#endif

#include "gamma.h"
#include "findUnion.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Tak ma wyglądać plansza po wykonaniu wszystkich testów.
 */

/** @brief Testuje silnik gry gamma.
 * Przeprowadza przykładowe testy silnika gry gamma.
 * @return Zero, gdy wszystkie testy przebiegły poprawnie,
 * a w przeciwnym przypadku kod zakończenia programu jest kodem błędu.
 */
int main() {
    gamma_t* board = gamma_new(4, 6, 2, 3);
    assert( board != NULL );


    assert( gamma_move(board, 1, 5, 2) == 0 );
    assert( gamma_move(board, 2, 0, 1) == 1 );
    assert( gamma_move(board, 1, 3, 0) == 1 );
    assert( gamma_move(board, 2, 2, 3) == 1 );
    assert( gamma_free_fields(board, 1) == 21 );
    assert( gamma_move(board, 1, 2, 3) == 0 );
    assert( gamma_move(board, 2, 0, 2) == 1 );
    assert( gamma_move(board, 1, 2, 0) == 1 );
    assert( gamma_move(board, 2, 1, 1) == 1 );
    assert( gamma_move(board, 1, 2, 0) == 0 );
    assert( gamma_move(board, 2, 5, 3) == 0 );
    assert( gamma_move(board, 2, 0, 0) == 1 );
    assert( gamma_busy_fields(board, 2) == 5 );
    assert( gamma_move(board, 1, 5, 1) == 0 );
    assert( gamma_move(board, 1, 0, 1) == 0 );
    assert( gamma_golden_possible(board, 1) == 1 );
    assert( gamma_move(board, 2, 0, 3) == 1 );
    assert( gamma_move(board, 2, 0, 5) == 1 );
    assert( gamma_move(board, 1, 1, 5) == 1 );
    assert( gamma_move(board, 1, 1, 4) == 1 );
    assert( gamma_move(board, 2, 5, 3) == 0 );
    assert( gamma_move(board, 1, 2, 1) == 1 );
    assert( gamma_move(board, 2, 2, 1) == 0 );
    assert( gamma_move(board, 1, 2, 3) == 0 );
    assert( gamma_move(board, 1, 3, 4) == 1 );
    assert( gamma_move(board, 2, 2, 1) == 0 );
    assert( gamma_move(board, 2, 2, 5) == 0 );
    assert( gamma_golden_possible(board, 2) == 1 );
    assert( gamma_move(board, 1, 4, 0) == 0 );
    assert( gamma_move(board, 2, 4, 2) == 0 );
    assert( gamma_move(board, 1, 2, 4) == 1 );
    assert( gamma_move(board, 1, 2, 4) == 0 );
    assert( gamma_busy_fields(board, 1) == 7 );
    assert( gamma_move(board, 2, 4, 0) == 0 );
    assert( gamma_move(board, 2, 0, 0) == 0 );
    assert( gamma_move(board, 1, 5, 3) == 0 );
    assert( gamma_move(board, 1, 2, 3) == 0 );
    assert( gamma_free_fields(board, 2) == 6 );
    assert( gamma_move(board, 1, 0, 0) == 0 );
    assert( gamma_move(board, 1, 3, 5) == 1 );
    assert( gamma_move(board, 2, 2, 5) == 0 );
    assert( gamma_move(board, 1, 2, 2) == 1 );
    assert( gamma_move(board, 2, 1, 2) == 1 );
    assert( gamma_move(board, 2, 2, 4) == 0 );
    assert( gamma_move(board, 1, 3, 3) == 1 );
    assert( gamma_move(board, 1, 3, 5) == 0 );
    assert( gamma_move(board, 2, 3, 1) == 0 );
    assert( gamma_move(board, 2, 0, 5) == 0 );
    assert( gamma_move(board, 1, 2, 0) == 0 );
    assert( gamma_move(board, 1, 1, 3) == 1 );
    char* b = gamma_board(board);
    printf("%s", b);
    free(b);
    assert( gamma_golden_move(board, 1, 0, 0) == 1 );


  /*  assert( gamma_move(board, 2, 2, 3) == 0 );
    assert( gamma_move(board, 2, 3, 1) == 0 );
    assert( gamma_move(board, 1, 2, 3) == 0 );
    assert( gamma_busy_fields(board, 1) == 12 );
    assert( gamma_free_fields(board, 1) == 5 );
    assert( gamma_move(board, 2, 5, 2) == 0 );
    assert( gamma_move(board, 2, 0, 4) == 1 );
    assert( gamma_move(board, 1, 2, 1) == 0 );
    assert( gamma_golden_possible(board, 1) == 0 );
    assert( gamma_move(board, 2, 1, 3) == 0 );
    assert( gamma_move(board, 2, 1, 4) == 0 );
    assert( gamma_move(board, 1, 3, 0) == 0 );
    assert( gamma_move(board, 2, 2, 3) == 0 );
    assert( gamma_busy_fields(board, 2) == 8 );
    assert( gamma_move(board, 1, 2, 3) == 0 );
    assert( gamma_move(board, 1, 2, 5) == 1 );
    assert( gamma_golden_possible(board, 1) == 0 );
    assert( gamma_move(board, 2, 1, 3) == 0 );
    assert( gamma_move(board, 2, 2, 4) == 0 );
    assert( gamma_golden_possible(board, 2) == 1 );
    assert( gamma_move(board, 1, 0, 4) == 0 );
    assert( gamma_move(board, 2, 0, 1) == 0 );
    assert( gamma_move(board, 2, 0, 3) == 0 );
    assert( gamma_golden_possible(board, 2) == 1 );
    assert( gamma_move(board, 1, 2, 1) == 0 );
    assert( gamma_move(board, 1, 1, 5) == 0 );
    assert( gamma_golden_possible(board, 1) == 0 );
    assert( gamma_move(board, 2, 1, 4) == 0 ); */


    gamma_delete(board);

    return 0;
}
