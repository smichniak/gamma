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
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {

/*
scenario: test_random_actions
uuid: 136904063
*/
/*
random actions, total chaos
*/
    gamma_t* board = gamma_new(9, 14, 6, 20);
    assert( board != NULL );


    assert( gamma_move(board, 1, 5, 3) == 1 );
    assert( gamma_move(board, 2, 9, 8) == 0 );
    assert( gamma_move(board, 2, 1, 1) == 1 );
    assert( gamma_move(board, 3, 3, 1) == 1 );
    assert( gamma_move(board, 4, 12, 1) == 0 );


    char* board418963378 = gamma_board(board);
    assert( board418963378 != NULL );
    assert( strcmp(board418963378,
                   ".........\n"
                   ".........\n"
                   ".........\n"
                   ".........\n"
                   ".........\n"
                   ".........\n"
                   ".........\n"
                   ".........\n"
                   ".........\n"
                   ".........\n"
                   ".....1...\n"
                   ".........\n"
                   ".2.3.....\n"
                   ".........\n") == 0);
    free(board418963378);
    board418963378 = NULL;
    assert( gamma_move(board, 5, 7, 2) == 1 );
    assert( gamma_move(board, 6, 6, 0) == 1 );
    assert( gamma_move(board, 6, 4, 10) == 1 );
    assert( gamma_move(board, 1, 7, 7) == 1 );
    assert( gamma_busy_fields(board, 1) == 2 );
    assert( gamma_move(board, 2, 2, 4) == 1 );
    assert( gamma_move(board, 2, 5, 12) == 1 );
    assert( gamma_move(board, 3, 1, 4) == 1 );
    assert( gamma_move(board, 3, 5, 9) == 1 );
    assert( gamma_free_fields(board, 3) == 115 );
    assert( gamma_move(board, 4, 5, 2) == 1 );
    assert( gamma_move(board, 4, 4, 12) == 1 );
    assert( gamma_move(board, 5, 3, 7) == 1 );
    assert( gamma_move(board, 5, 5, 4) == 1 );
    assert( gamma_golden_possible(board, 5) == 1 );
    assert( gamma_move(board, 6, 4, 7) == 1 );
    assert( gamma_move(board, 6, 2, 9) == 1 );
    assert( gamma_move(board, 1, 4, 4) == 1 );
    assert( gamma_move(board, 1, 5, 2) == 0 );
    assert( gamma_move(board, 2, 11, 6) == 0 );
    assert( gamma_busy_fields(board, 2) == 3 );
    assert( gamma_move(board, 3, 6, 7) == 1 );
    assert( gamma_busy_fields(board, 3) == 4 );
    assert( gamma_move(board, 4, 5, 0) == 1 );
    assert( gamma_move(board, 5, 13, 0) == 0 );
    assert( gamma_move(board, 6, 6, 0) == 0 );
    assert( gamma_move(board, 1, 0, 5) == 1 );
    assert( gamma_move(board, 2, 10, 3) == 0 );
    assert( gamma_move(board, 3, 4, 6) == 1 );
    assert( gamma_move(board, 4, 11, 5) == 0 );
    assert( gamma_move(board, 5, 8, 7) == 1 );
    assert( gamma_move(board, 6, 4, 2) == 1 );
    assert( gamma_move(board, 6, 3, 12) == 1 );
    assert( gamma_move(board, 1, 3, 13) == 1 );
    assert( gamma_golden_possible(board, 1) == 1 );
    assert( gamma_move(board, 2, 7, 2) == 0 );
    assert( gamma_move(board, 2, 5, 5) == 1 );
    assert( gamma_move(board, 3, 4, 1) == 1 );
    assert( gamma_move(board, 3, 8, 12) == 1 );
    assert( gamma_busy_fields(board, 3) == 7 );
    assert( gamma_move(board, 4, 2, 1) == 1 );
    assert( gamma_move(board, 4, 2, 11) == 1 );
    assert( gamma_move(board, 5, 5, 12) == 0 );
    assert( gamma_busy_fields(board, 5) == 4 );
    assert( gamma_move(board, 6, 6, 3) == 1 );
    assert( gamma_move(board, 1, 6, 1) == 1 );
    assert( gamma_move(board, 2, 5, 7) == 1 );
    assert( gamma_move(board, 2, 7, 9) == 1 );
    assert( gamma_move(board, 3, 4, 7) == 0 );
    assert( gamma_move(board, 3, 3, 4) == 1 );
    assert( gamma_golden_possible(board, 3) == 1 );
    assert( gamma_move(board, 4, 5, 4) == 0 );
    assert( gamma_move(board, 4, 6, 13) == 1 );
    assert( gamma_free_fields(board, 5) == 89 );
    assert( gamma_move(board, 6, 0, 6) == 1 );
    assert( gamma_free_fields(board, 6) == 88 );


    char* board838994933 = gamma_board(board);
    assert( board838994933 != NULL );
    assert( strcmp(board838994933,
                   "...1..4..\n"
                   "...642..3\n"
                   "..4......\n"
                   "....6....\n"
                   "..6..3.2.\n"
                   ".........\n"
                   "...562315\n"
                   "6...3....\n"
                   "1....2...\n"
                   ".32315...\n"
                   ".....16..\n"
                   "....64.5.\n"
                   ".2433.1..\n"
                   ".....46..\n") == 0);
    free(board838994933);
    board838994933 = NULL;
    assert( gamma_move(board, 1, 11, 1) == 0 );
    assert( gamma_free_fields(board, 1) == 88 );
    assert( gamma_move(board, 3, 1, 0) == 1 );
    assert( gamma_move(board, 3, 1, 6) == 1 );
    assert( gamma_move(board, 4, 3, 4) == 0 );
    assert( gamma_move(board, 4, 6, 1) == 0 );
    assert( gamma_move(board, 5, 8, 7) == 0 );
    assert( gamma_move(board, 6, 8, 2) == 1 );
    assert( gamma_move(board, 6, 1, 1) == 0 );
    assert( gamma_move(board, 1, 4, 0) == 1 );
    assert( gamma_move(board, 1, 5, 11) == 1 );
    assert( gamma_move(board, 2, 6, 8) == 1 );
    assert( gamma_move(board, 2, 1, 6) == 0 );
    assert( gamma_move(board, 3, 5, 6) == 1 );
    assert( gamma_move(board, 4, 8, 3) == 1 );
    assert( gamma_busy_fields(board, 5) == 4 );
    assert( gamma_move(board, 1, 8, 3) == 0 );
    assert( gamma_move(board, 2, 5, 3) == 0 );
    assert( gamma_move(board, 2, 4, 4) == 0 );
    assert( gamma_move(board, 3, 6, 8) == 0 );
    assert( gamma_move(board, 3, 8, 4) == 1 );
    assert( gamma_move(board, 4, 8, 7) == 0 );
    assert( gamma_move(board, 5, 10, 0) == 0 );
    assert( gamma_move(board, 5, 8, 0) == 1 );
    assert( gamma_free_fields(board, 5) == 78 );
    assert( gamma_move(board, 6, 1, 7) == 1 );
    assert( gamma_move(board, 6, 8, 0) == 0 );


    char* board608950959 = gamma_board(board);
    assert( board608950959 != NULL );
    assert( strcmp(board608950959,
                   "...1..4..\n"
                   "...642..3\n"
                   "..4..1...\n"
                   "....6....\n"
                   "..6..3.2.\n"
                   "......2..\n"
                   ".6.562315\n"
                   "63..33...\n"
                   "1....2...\n"
                   ".32315..3\n"
                   ".....16.4\n"
                   "....64.56\n"
                   ".2433.1..\n"
                   ".3..146.5\n") == 0);
    free(board608950959);
    board608950959 = NULL;
    assert( gamma_move(board, 2, 4, 5) == 1 );
    assert( gamma_move(board, 2, 5, 8) == 1 );
    assert( gamma_move(board, 3, 8, 7) == 0 );
    assert( gamma_move(board, 3, 0, 11) == 1 );
    assert( gamma_move(board, 4, 2, 12) == 1 );


    char* board973071442 = gamma_board(board);
    assert( board973071442 != NULL );
    assert( strcmp(board973071442,
                   "...1..4..\n"
                   "..4642..3\n"
                   "3.4..1...\n"
                   "....6....\n"
                   "..6..3.2.\n"
                   ".....22..\n"
                   ".6.562315\n"
                   "63..33...\n"
                   "1...22...\n"
                   ".32315..3\n"
                   ".....16.4\n"
                   "....64.56\n"
                   ".2433.1..\n"
                   ".3..146.5\n") == 0);
    free(board973071442);
    board973071442 = NULL;
    assert( gamma_move(board, 6, 4, 9) == 1 );
    assert( gamma_move(board, 1, 7, 6) == 1 );
    assert( gamma_golden_possible(board, 1) == 1 );
    assert( gamma_move(board, 2, 3, 7) == 0 );


    char* board228095439 = gamma_board(board);
    assert( board228095439 != NULL );
    assert( strcmp(board228095439,
                   "...1..4..\n"
                   "..4642..3\n"
                   "3.4..1...\n"
                   "....6....\n"
                   "..6.63.2.\n"
                   ".....22..\n"
                   ".6.562315\n"
                   "63..33.1.\n"
                   "1...22...\n"
                   ".32315..3\n"
                   ".....16.4\n"
                   "....64.56\n"
                   ".2433.1..\n"
                   ".3..146.5\n") == 0);
    free(board228095439);
    board228095439 = NULL;
    assert( gamma_move(board, 3, 8, 4) == 0 );
    assert( gamma_golden_possible(board, 3) == 1 );
    assert( gamma_move(board, 5, 11, 1) == 0 );
    assert( gamma_move(board, 5, 7, 2) == 0 );
    assert( gamma_busy_fields(board, 5) == 5 );
    assert( gamma_golden_move(board, 5, 3, 5) == 0 );
    assert( gamma_move(board, 6, 3, 11) == 1 );
    assert( gamma_move(board, 6, 4, 12) == 0 );
    assert( gamma_golden_possible(board, 6) == 1 );
    assert( gamma_move(board, 1, 3, 1) == 0 );
    assert( gamma_move(board, 2, 3, 9) == 1 );
    assert( gamma_move(board, 3, 1, 0) == 0 );
    assert( gamma_free_fields(board, 3) == 69 );
    assert( gamma_move(board, 4, 9, 1) == 0 );
    assert( gamma_move(board, 4, 7, 9) == 0 );
    assert( gamma_move(board, 5, 13, 5) == 0 );
    assert( gamma_move(board, 5, 7, 11) == 1 );
    assert( gamma_golden_possible(board, 5) == 1 );
    assert( gamma_move(board, 6, 3, 8) == 1 );
    assert( gamma_move(board, 1, 10, 3) == 0 );
    assert( gamma_busy_fields(board, 1) == 9 );
    assert( gamma_move(board, 2, 1, 4) == 0 );
    assert( gamma_move(board, 2, 2, 8) == 1 );
    assert( gamma_busy_fields(board, 2) == 11 );
    assert( gamma_move(board, 3, 2, 1) == 0 );
    assert( gamma_move(board, 3, 8, 6) == 1 );
    assert( gamma_move(board, 4, 11, 4) == 0 );
    assert( gamma_move(board, 4, 4, 4) == 0 );
    assert( gamma_move(board, 5, 6, 7) == 0 );


    char* board334690500 = gamma_board(board);
    assert( board334690500 != NULL );
    assert( strcmp(board334690500,
                   "...1..4..\n"
                   "..4642..3\n"
                   "3.46.1.5.\n"
                   "....6....\n"
                   "..6263.2.\n"
                   "..26.22..\n"
                   ".6.562315\n"
                   "63..33.13\n"
                   "1...22...\n"
                   ".32315..3\n"
                   ".....16.4\n"
                   "....64.56\n"
                   ".2433.1..\n"
                   ".3..146.5\n") == 0);
    free(board334690500);
    board334690500 = NULL;
    assert( gamma_move(board, 6, 6, 3) == 0 );
    assert( gamma_golden_possible(board, 6) == 1 );
    assert( gamma_move(board, 1, 9, 6) == 0 );
    assert( gamma_golden_possible(board, 1) == 1 );
    assert( gamma_move(board, 2, 2, 0) == 1 );
    assert( gamma_move(board, 3, 1, 7) == 0 );
    assert( gamma_move(board, 4, 13, 7) == 0 );
    assert( gamma_move(board, 5, 7, 0) == 1 );
    assert( gamma_move(board, 5, 2, 1) == 0 );


    char* board988406180 = gamma_board(board);
    assert( board988406180 != NULL );
    assert( strcmp(board988406180,
                   "...1..4..\n"
                   "..4642..3\n"
                   "3.46.1.5.\n"
                   "....6....\n"
                   "..6263.2.\n"
                   "..26.22..\n"
                   ".6.562315\n"
                   "63..33.13\n"
                   "1...22...\n"
                   ".32315..3\n"
                   ".....16.4\n"
                   "....64.56\n"
                   ".2433.1..\n"
                   ".32.14655\n") == 0);
    free(board988406180);
    board988406180 = NULL;
    assert( gamma_move(board, 6, 2, 0) == 0 );
    assert( gamma_move(board, 6, 5, 3) == 0 );
    assert( gamma_golden_move(board, 6, 9, 3) == 0 );
    assert( gamma_move(board, 1, 11, 4) == 0 );
    assert( gamma_move(board, 1, 2, 6) == 1 );
    assert( gamma_free_fields(board, 1) == 62 );
    assert( gamma_move(board, 2, 4, 7) == 0 );
    assert( gamma_move(board, 2, 2, 3) == 1 );
    assert( gamma_move(board, 3, 5, 10) == 1 );
    assert( gamma_golden_move(board, 3, 11, 7) == 0 );
    assert( gamma_move(board, 4, 3, 9) == 0 );
    assert( gamma_move(board, 4, 2, 13) == 1 );
    assert( gamma_move(board, 5, 11, 4) == 0 );
    assert( gamma_move(board, 5, 5, 13) == 1 );
    assert( gamma_move(board, 6, 13, 1) == 0 );
    assert( gamma_move(board, 6, 6, 12) == 1 );
    assert( gamma_move(board, 1, 8, 8) == 1 );
    assert( gamma_busy_fields(board, 1) == 11 );
    assert( gamma_move(board, 2, 1, 10) == 1 );
    assert( gamma_move(board, 2, 6, 9) == 1 );
    assert( gamma_move(board, 3, 7, 0) == 0 );
    assert( gamma_move(board, 4, 9, 8) == 0 );
    assert( gamma_move(board, 5, 3, 4) == 0 );
    assert( gamma_move(board, 6, 6, 3) == 0 );
    assert( gamma_move(board, 1, 4, 6) == 0 );
    assert( gamma_free_fields(board, 1) == 54 );
    assert( gamma_golden_move(board, 1, 4, 5) == 1 );
    assert( gamma_move(board, 2, 4, 6) == 0 );
    assert( gamma_move(board, 2, 5, 8) == 0 );
    assert( gamma_golden_possible(board, 2) == 1 );
    assert( gamma_move(board, 3, 9, 1) == 0 );
    assert( gamma_move(board, 3, 7, 4) == 1 );


    char* board113285364 = gamma_board(board);
    assert( board113285364 != NULL );
    assert( strcmp(board113285364,
                   "..41.54..\n"
                   "..46426.3\n"
                   "3.46.1.5.\n"
                   ".2..63...\n"
                   "..626322.\n"
                   "..26.22.1\n"
                   ".6.562315\n"
                   "631.33.13\n"
                   "1...12...\n"
                   ".32315.33\n"
                   "..2..16.4\n"
                   "....64.56\n"
                   ".2433.1..\n"
                   ".32.14655\n") == 0);
    free(board113285364);
    board113285364 = NULL;
    assert( gamma_move(board, 4, 3, 3) == 1 );
    assert( gamma_move(board, 6, 10, 2) == 0 );
    assert( gamma_move(board, 6, 2, 6) == 0 );
    assert( gamma_move(board, 1, 6, 3) == 0 );
    assert( gamma_free_fields(board, 1) == 52 );
    assert( gamma_move(board, 2, 0, 2) == 1 );
    assert( gamma_move(board, 2, 0, 2) == 0 );
    assert( gamma_golden_move(board, 2, 2, 7) == 0 );
    assert( gamma_move(board, 3, 12, 1) == 0 );
    assert( gamma_golden_possible(board, 3) == 1 );
    assert( gamma_move(board, 4, 1, 7) == 0 );
    assert( gamma_move(board, 4, 2, 12) == 0 );
    assert( gamma_busy_fields(board, 4) == 10 );
    assert( gamma_move(board, 5, 7, 0) == 0 );
    assert( gamma_free_fields(board, 5) == 51 );
    assert( gamma_move(board, 6, 1, 0) == 0 );
    assert( gamma_move(board, 6, 5, 5) == 0 );
    assert( gamma_move(board, 1, 3, 4) == 0 );
    assert( gamma_move(board, 1, 3, 3) == 0 );
    assert( gamma_move(board, 2, 3, 6) == 1 );
    assert( gamma_move(board, 3, 8, 12) == 0 );
    assert( gamma_move(board, 4, 5, 2) == 0 );
    assert( gamma_busy_fields(board, 4) == 10 );
    assert( gamma_move(board, 5, 1, 7) == 0 );
    assert( gamma_move(board, 5, 8, 5) == 1 );
    assert( gamma_golden_possible(board, 5) == 1 );
    assert( gamma_move(board, 6, 12, 1) == 0 );
    assert( gamma_move(board, 1, 5, 3) == 0 );
    assert( gamma_move(board, 1, 8, 7) == 0 );
    assert( gamma_move(board, 2, 8, 1) == 1 );
    assert( gamma_move(board, 2, 7, 10) == 1 );
    assert( gamma_move(board, 3, 3, 4) == 0 );
    assert( gamma_busy_fields(board, 3) == 16 );
    assert( gamma_move(board, 4, 13, 8) == 0 );
    assert( gamma_move(board, 4, 8, 3) == 0 );
    assert( gamma_move(board, 5, 8, 5) == 0 );
    assert( gamma_busy_fields(board, 5) == 9 );
    assert( gamma_move(board, 6, 0, 0) == 1 );
    assert( gamma_free_fields(board, 6) == 46 );
    assert( gamma_move(board, 1, 8, 0) == 0 );
    assert( gamma_move(board, 3, 5, 7) == 0 );
    assert( gamma_move(board, 3, 6, 5) == 1 );
    assert( gamma_busy_fields(board, 3) == 17 );
    assert( gamma_move(board, 4, 4, 4) == 0 );
    assert( gamma_move(board, 4, 5, 7) == 0 );
    assert( gamma_busy_fields(board, 4) == 10 );
    assert( gamma_move(board, 5, 5, 9) == 0 );
    assert( gamma_move(board, 6, 7, 0) == 0 );
    assert( gamma_move(board, 1, 10, 3) == 0 );
    assert( gamma_free_fields(board, 1) == 45 );
    assert( gamma_move(board, 2, 7, 0) == 0 );
    assert( gamma_busy_fields(board, 2) == 18 );


    char* board686893453 = gamma_board(board);
    assert( board686893453 != NULL );
    assert( strcmp(board686893453,
                   "..41.54..\n"
                   "..46426.3\n"
                   "3.46.1.5.\n"
                   ".2..63.2.\n"
                   "..626322.\n"
                   "..26.22.1\n"
                   ".6.562315\n"
                   "631233.13\n"
                   "1...123.5\n"
                   ".32315.33\n"
                   "..24.16.4\n"
                   "2...64.56\n"
                   ".2433.1.2\n"
                   "632.14655\n") == 0);
    free(board686893453);
    board686893453 = NULL;
    assert( gamma_move(board, 3, 8, 5) == 0 );
    assert( gamma_move(board, 4, 5, 7) == 0 );
    assert( gamma_free_fields(board, 4) == 45 );


    char* board549045748 = gamma_board(board);
    assert( board549045748 != NULL );
    assert( strcmp(board549045748,
                   "..41.54..\n"
                   "..46426.3\n"
                   "3.46.1.5.\n"
                   ".2..63.2.\n"
                   "..626322.\n"
                   "..26.22.1\n"
                   ".6.562315\n"
                   "631233.13\n"
                   "1...123.5\n"
                   ".32315.33\n"
                   "..24.16.4\n"
                   "2...64.56\n"
                   ".2433.1.2\n"
                   "632.14655\n") == 0);
    free(board549045748);
    board549045748 = NULL;
    assert( gamma_move(board, 5, 3, 4) == 0 );
    assert( gamma_move(board, 6, 9, 8) == 0 );
    assert( gamma_move(board, 1, 10, 6) == 0 );
    assert( gamma_move(board, 2, 4, 9) == 0 );
    assert( gamma_move(board, 2, 0, 1) == 1 );
    assert( gamma_move(board, 3, 7, 2) == 0 );
    assert( gamma_move(board, 4, 0, 3) == 1 );
    assert( gamma_move(board, 5, 0, 13) == 1 );
    assert( gamma_move(board, 6, 4, 8) == 1 );
    assert( gamma_move(board, 1, 2, 6) == 0 );
    assert( gamma_move(board, 2, 4, 3) == 1 );
    assert( gamma_move(board, 2, 6, 9) == 0 );


    char* board924901582 = gamma_board(board);
    assert( board924901582 != NULL );
    assert( strcmp(board924901582,
                   "5.41.54..\n"
                   "..46426.3\n"
                   "3.46.1.5.\n"
                   ".2..63.2.\n"
                   "..626322.\n"
                   "..26622.1\n"
                   ".6.562315\n"
                   "631233.13\n"
                   "1...123.5\n"
                   ".32315.33\n"
                   "4.24216.4\n"
                   "2...64.56\n"
                   "22433.1.2\n"
                   "632.14655\n") == 0);
    free(board924901582);
    board924901582 = NULL;
    assert( gamma_move(board, 3, 9, 0) == 0 );
    assert( gamma_move(board, 3, 6, 13) == 0 );
    assert( gamma_golden_move(board, 3, 3, 8) == 1 );
    assert( gamma_move(board, 4, 5, 12) == 0 );
    assert( gamma_move(board, 4, 1, 9) == 1 );
    assert( gamma_free_fields(board, 4) == 39 );
    assert( gamma_golden_possible(board, 4) == 1 );
    assert( gamma_move(board, 5, 1, 6) == 0 );
    assert( gamma_move(board, 5, 8, 1) == 0 );
    assert( gamma_move(board, 6, 0, 4) == 1 );
    assert( gamma_move(board, 6, 2, 6) == 0 );
    assert( gamma_move(board, 1, 2, 5) == 1 );
    assert( gamma_busy_fields(board, 1) == 13 );
    assert( gamma_busy_fields(board, 2) == 20 );


    char* board476175398 = gamma_board(board);
    assert( board476175398 != NULL );
    assert( strcmp(board476175398,
                   "5.41.54..\n"
                   "..46426.3\n"
                   "3.46.1.5.\n"
                   ".2..63.2.\n"
                   ".4626322.\n"
                   "..23622.1\n"
                   ".6.562315\n"
                   "631233.13\n"
                   "1.1.123.5\n"
                   "632315.33\n"
                   "4.24216.4\n"
                   "2...64.56\n"
                   "22433.1.2\n"
                   "632.14655\n") == 0);
    free(board476175398);
    board476175398 = NULL;
    assert( gamma_move(board, 3, 5, 3) == 0 );
    assert( gamma_golden_possible(board, 3) == 0 );
    assert( gamma_move(board, 4, 1, 5) == 1 );
    assert( gamma_move(board, 4, 1, 6) == 0 );


    char* board269082086 = gamma_board(board);
    assert( board269082086 != NULL );
    assert( strcmp(board269082086,
                   "5.41.54..\n"
                   "..46426.3\n"
                   "3.46.1.5.\n"
                   ".2..63.2.\n"
                   ".4626322.\n"
                   "..23622.1\n"
                   ".6.562315\n"
                   "631233.13\n"
                   "141.123.5\n"
                   "632315.33\n"
                   "4.24216.4\n"
                   "2...64.56\n"
                   "22433.1.2\n"
                   "632.14655\n") == 0);
    free(board269082086);
    board269082086 = NULL;
    assert( gamma_move(board, 5, 8, 1) == 0 );
    assert( gamma_move(board, 5, 3, 12) == 0 );
    assert( gamma_golden_possible(board, 5) == 1 );


    char* board253447203 = gamma_board(board);
    assert( board253447203 != NULL );
    assert( strcmp(board253447203,
                   "5.41.54..\n"
                   "..46426.3\n"
                   "3.46.1.5.\n"
                   ".2..63.2.\n"
                   ".4626322.\n"
                   "..23622.1\n"
                   ".6.562315\n"
                   "631233.13\n"
                   "141.123.5\n"
                   "632315.33\n"
                   "4.24216.4\n"
                   "2...64.56\n"
                   "22433.1.2\n"
                   "632.14655\n") == 0);
    free(board253447203);
    board253447203 = NULL;
    assert( gamma_move(board, 6, 11, 4) == 0 );
    assert( gamma_move(board, 6, 5, 13) == 0 );
    assert( gamma_move(board, 2, 9, 8) == 0 );
    assert( gamma_move(board, 2, 6, 6) == 1 );
    assert( gamma_move(board, 3, 8, 1) == 0 );
    assert( gamma_move(board, 3, 8, 9) == 1 );
    assert( gamma_move(board, 4, 2, 2) == 1 );
    assert( gamma_move(board, 4, 3, 1) == 0 );
    assert( gamma_move(board, 5, 2, 3) == 0 );
    assert( gamma_move(board, 5, 5, 11) == 0 );
    assert( gamma_move(board, 6, 11, 6) == 0 );
    assert( gamma_move(board, 1, 4, 11) == 1 );
    assert( gamma_move(board, 2, 2, 6) == 0 );
    assert( gamma_move(board, 3, 13, 7) == 0 );
    assert( gamma_move(board, 3, 8, 13) == 1 );
    assert( gamma_move(board, 4, 2, 1) == 0 );
    assert( gamma_move(board, 5, 5, 3) == 0 );
    assert( gamma_move(board, 5, 2, 2) == 0 );
    assert( gamma_busy_fields(board, 5) == 10 );
    assert( gamma_free_fields(board, 5) == 31 );


    char* board601871685 = gamma_board(board);
    assert( board601871685 != NULL );
    assert( strcmp(board601871685,
                   "5.41.54.3\n"
                   "..46426.3\n"
                   "3.4611.5.\n"
                   ".2..63.2.\n"
                   ".46263223\n"
                   "..23622.1\n"
                   ".6.562315\n"
                   "631233213\n"
                   "141.123.5\n"
                   "632315.33\n"
                   "4.24216.4\n"
                   "2.4.64.56\n"
                   "22433.1.2\n"
                   "632.14655\n") == 0);
    free(board601871685);
    board601871685 = NULL;
    assert( gamma_move(board, 6, 0, 5) == 0 );
    assert( gamma_move(board, 1, 8, 12) == 0 );
    assert( gamma_move(board, 1, 8, 10) == 1 );
    assert( gamma_move(board, 2, 4, 6) == 0 );
    assert( gamma_move(board, 3, 6, 8) == 0 );
    assert( gamma_move(board, 4, 11, 6) == 0 );
    assert( gamma_move(board, 4, 1, 13) == 1 );
    assert( gamma_move(board, 6, 9, 0) == 0 );
    assert( gamma_move(board, 1, 13, 7) == 0 );
    assert( gamma_move(board, 1, 2, 5) == 0 );
    assert( gamma_golden_move(board, 1, 5, 1) == 0 );
    assert( gamma_move(board, 2, 3, 11) == 0 );
    assert( gamma_move(board, 3, 11, 1) == 0 );
    assert( gamma_move(board, 3, 8, 9) == 0 );
    assert( gamma_move(board, 4, 2, 3) == 0 );
    assert( gamma_move(board, 5, 0, 3) == 0 );
    assert( gamma_free_fields(board, 5) == 29 );
    assert( gamma_move(board, 1, 4, 6) == 0 );
    assert( gamma_move(board, 1, 4, 1) == 0 );
    assert( gamma_move(board, 2, 2, 5) == 0 );
    assert( gamma_move(board, 2, 8, 8) == 0 );
    assert( gamma_move(board, 3, 5, 8) == 0 );
    assert( gamma_golden_possible(board, 3) == 0 );
    assert( gamma_move(board, 4, 2, 6) == 0 );
    assert( gamma_move(board, 5, 1, 5) == 0 );
    assert( gamma_move(board, 6, 6, 11) == 1 );
    assert( gamma_golden_possible(board, 6) == 1 );
    assert( gamma_move(board, 1, 2, 8) == 0 );
    assert( gamma_move(board, 1, 4, 9) == 0 );
    assert( gamma_free_fields(board, 1) == 28 );
    assert( gamma_move(board, 2, 2, 3) == 0 );
    assert( gamma_move(board, 3, 8, 12) == 0 );
    assert( gamma_move(board, 4, 3, 7) == 0 );
    assert( gamma_move(board, 5, 0, 3) == 0 );
    assert( gamma_move(board, 5, 1, 4) == 0 );
    assert( gamma_move(board, 6, 1, 5) == 0 );
    assert( gamma_move(board, 6, 5, 10) == 0 );
    assert( gamma_free_fields(board, 6) == 28 );
    assert( gamma_move(board, 1, 5, 2) == 0 );
    assert( gamma_move(board, 1, 1, 12) == 1 );
    assert( gamma_busy_fields(board, 1) == 16 );
    assert( gamma_move(board, 2, 10, 2) == 0 );
    assert( gamma_move(board, 2, 8, 4) == 0 );
    assert( gamma_move(board, 3, 10, 2) == 0 );
    assert( gamma_move(board, 3, 0, 4) == 0 );
    assert( gamma_move(board, 4, 1, 7) == 0 );
    assert( gamma_move(board, 4, 3, 3) == 0 );
    assert( gamma_move(board, 5, 2, 6) == 0 );
    assert( gamma_move(board, 5, 1, 2) == 1 );


    char* board573122900 = gamma_board(board);
    assert( board573122900 != NULL );
    assert( strcmp(board573122900,
                   "5441.54.3\n"
                   ".146426.3\n"
                   "3.461165.\n"
                   ".2..63.21\n"
                   ".46263223\n"
                   "..23622.1\n"
                   ".6.562315\n"
                   "631233213\n"
                   "141.123.5\n"
                   "632315.33\n"
                   "4.24216.4\n"
                   "254.64.56\n"
                   "22433.1.2\n"
                   "632.14655\n") == 0);
    free(board573122900);
    board573122900 = NULL;
    assert( gamma_move(board, 6, 10, 0) == 0 );
    assert( gamma_busy_fields(board, 6) == 17 );
    assert( gamma_move(board, 1, 1, 10) == 0 );
    assert( gamma_move(board, 1, 1, 12) == 0 );
    assert( gamma_move(board, 2, 8, 0) == 0 );
    assert( gamma_move(board, 2, 8, 10) == 0 );
    assert( gamma_free_fields(board, 2) == 26 );
    assert( gamma_move(board, 3, 0, 6) == 0 );
    assert( gamma_move(board, 3, 5, 0) == 0 );
    assert( gamma_busy_fields(board, 3) == 20 );
    assert( gamma_move(board, 4, 7, 2) == 0 );
    assert( gamma_move(board, 4, 1, 5) == 0 );
    assert( gamma_move(board, 5, 5, 7) == 0 );
    assert( gamma_move(board, 6, 10, 3) == 0 );


    char* board396557111 = gamma_board(board);
    assert( board396557111 != NULL );
    assert( strcmp(board396557111,
                   "5441.54.3\n"
                   ".146426.3\n"
                   "3.461165.\n"
                   ".2..63.21\n"
                   ".46263223\n"
                   "..23622.1\n"
                   ".6.562315\n"
                   "631233213\n"
                   "141.123.5\n"
                   "632315.33\n"
                   "4.24216.4\n"
                   "254.64.56\n"
                   "22433.1.2\n"
                   "632.14655\n") == 0);
    free(board396557111);
    board396557111 = NULL;
    assert( gamma_move(board, 2, 9, 0) == 0 );
    assert( gamma_move(board, 3, 8, 7) == 0 );
    assert( gamma_move(board, 4, 8, 7) == 0 );
    assert( gamma_free_fields(board, 4) == 26 );
    assert( gamma_golden_possible(board, 4) == 1 );
    assert( gamma_move(board, 5, 6, 1) == 0 );
    assert( gamma_move(board, 6, 2, 3) == 0 );
    assert( gamma_move(board, 1, 1, 7) == 0 );
    assert( gamma_move(board, 1, 5, 0) == 0 );
    assert( gamma_move(board, 2, 2, 3) == 0 );
    assert( gamma_move(board, 2, 1, 2) == 0 );
    assert( gamma_move(board, 3, 12, 7) == 0 );
    assert( gamma_move(board, 3, 7, 2) == 0 );
    assert( gamma_golden_possible(board, 3) == 0 );
    assert( gamma_free_fields(board, 4) == 26 );
    assert( gamma_move(board, 5, 5, 5) == 0 );
    assert( gamma_move(board, 5, 5, 2) == 0 );
    assert( gamma_golden_possible(board, 5) == 1 );
    assert( gamma_move(board, 6, 10, 2) == 0 );
    assert( gamma_move(board, 2, 5, 7) == 0 );
    assert( gamma_move(board, 2, 8, 1) == 0 );
    assert( gamma_move(board, 3, 2, 3) == 0 );
    assert( gamma_move(board, 3, 6, 5) == 0 );
    assert( gamma_free_fields(board, 3) == 26 );
    assert( gamma_move(board, 4, 5, 0) == 0 );
    assert( gamma_busy_fields(board, 4) == 15 );
    assert( gamma_move(board, 5, 11, 8) == 0 );
    assert( gamma_move(board, 6, 2, 0) == 0 );
    assert( gamma_move(board, 1, 13, 7) == 0 );
    assert( gamma_move(board, 1, 4, 0) == 0 );


    char* board848732053 = gamma_board(board);
    assert( board848732053 != NULL );
    assert( strcmp(board848732053,
                   "5441.54.3\n"
                   ".146426.3\n"
                   "3.461165.\n"
                   ".2..63.21\n"
                   ".46263223\n"
                   "..23622.1\n"
                   ".6.562315\n"
                   "631233213\n"
                   "141.123.5\n"
                   "632315.33\n"
                   "4.24216.4\n"
                   "254.64.56\n"
                   "22433.1.2\n"
                   "632.14655\n") == 0);
    free(board848732053);
    board848732053 = NULL;
    assert( gamma_move(board, 2, 2, 6) == 0 );
    assert( gamma_golden_move(board, 2, 13, 2) == 0 );
    assert( gamma_move(board, 3, 3, 1) == 0 );
    assert( gamma_move(board, 4, 1, 7) == 0 );
    assert( gamma_move(board, 5, 0, 3) == 0 );
    assert( gamma_move(board, 5, 5, 0) == 0 );
    assert( gamma_golden_possible(board, 5) == 1 );
    assert( gamma_move(board, 6, 7, 2) == 0 );
    assert( gamma_golden_possible(board, 6) == 1 );
    assert( gamma_move(board, 1, 2, 4) == 0 );
    assert( gamma_move(board, 1, 0, 1) == 0 );
    assert( gamma_move(board, 2, 13, 4) == 0 );
    assert( gamma_move(board, 2, 5, 8) == 0 );
    assert( gamma_golden_possible(board, 2) == 1 );
    assert( gamma_move(board, 3, 8, 0) == 0 );
    assert( gamma_golden_possible(board, 3) == 0 );
    assert( gamma_move(board, 4, 11, 1) == 0 );
    assert( gamma_move(board, 5, 8, 7) == 0 );
    assert( gamma_free_fields(board, 5) == 26 );
    assert( gamma_move(board, 6, 11, 1) == 0 );
    assert( gamma_move(board, 6, 1, 8) == 1 );
    assert( gamma_golden_move(board, 6, 12, 8) == 0 );
    assert( gamma_move(board, 1, 2, 6) == 0 );
    assert( gamma_move(board, 1, 2, 9) == 0 );
    assert( gamma_move(board, 3, 8, 12) == 0 );
    assert( gamma_move(board, 4, 8, 11) == 1 );
    assert( gamma_move(board, 4, 5, 1) == 1 );
    assert( gamma_move(board, 5, 8, 7) == 0 );


    char* board984230501 = gamma_board(board);
    assert( board984230501 != NULL );
    assert( strcmp(board984230501,
                   "5441.54.3\n"
                   ".146426.3\n"
                   "3.4611654\n"
                   ".2..63.21\n"
                   ".46263223\n"
                   ".623622.1\n"
                   ".6.562315\n"
                   "631233213\n"
                   "141.123.5\n"
                   "632315.33\n"
                   "4.24216.4\n"
                   "254.64.56\n"
                   "2243341.2\n"
                   "632.14655\n") == 0);
    free(board984230501);
    board984230501 = NULL;
    assert( gamma_move(board, 6, 11, 1) == 0 );
    assert( gamma_move(board, 6, 4, 4) == 0 );
    assert( gamma_move(board, 1, 4, 6) == 0 );
    assert( gamma_free_fields(board, 1) == 23 );
    assert( gamma_move(board, 2, 13, 4) == 0 );
    assert( gamma_move(board, 3, 12, 7) == 0 );
    assert( gamma_move(board, 3, 7, 11) == 0 );
    assert( gamma_move(board, 4, 3, 1) == 0 );
    assert( gamma_move(board, 4, 1, 13) == 0 );
    assert( gamma_move(board, 5, 3, 7) == 0 );
    assert( gamma_move(board, 6, 0, 3) == 0 );
    assert( gamma_move(board, 6, 8, 7) == 0 );
    assert( gamma_move(board, 1, 8, 10) == 0 );
    assert( gamma_move(board, 1, 4, 12) == 0 );
    assert( gamma_golden_possible(board, 1) == 0 );
    assert( gamma_move(board, 2, 3, 11) == 0 );
    assert( gamma_move(board, 3, 8, 4) == 0 );
    assert( gamma_move(board, 3, 6, 8) == 0 );
    assert( gamma_move(board, 4, 8, 0) == 0 );
    assert( gamma_move(board, 5, 4, 6) == 0 );
    assert( gamma_move(board, 5, 8, 1) == 0 );
    assert( gamma_move(board, 6, 0, 3) == 0 );


    char* board488504702 = gamma_board(board);
    assert( board488504702 != NULL );
    assert( strcmp(board488504702,
                   "5441.54.3\n"
                   ".146426.3\n"
                   "3.4611654\n"
                   ".2..63.21\n"
                   ".46263223\n"
                   ".623622.1\n"
                   ".6.562315\n"
                   "631233213\n"
                   "141.123.5\n"
                   "632315.33\n"
                   "4.24216.4\n"
                   "254.64.56\n"
                   "2243341.2\n"
                   "632.14655\n") == 0);
    free(board488504702);
    board488504702 = NULL;
    assert( gamma_move(board, 1, 7, 3) == 1 );
    assert( gamma_free_fields(board, 2) == 22 );
    assert( gamma_golden_move(board, 2, 8, 3) == 1 );
    assert( gamma_move(board, 3, 5, 7) == 0 );
    assert( gamma_move(board, 3, 6, 4) == 1 );


    char* board351782329 = gamma_board(board);
    assert( board351782329 != NULL );
    assert( strcmp(board351782329,
                   "5441.54.3\n"
                   ".146426.3\n"
                   "3.4611654\n"
                   ".2..63.21\n"
                   ".46263223\n"
                   ".623622.1\n"
                   ".6.562315\n"
                   "631233213\n"
                   "141.123.5\n"
                   "632315333\n"
                   "4.2421612\n"
                   "254.64.56\n"
                   "2243341.2\n"
                   "632.14655\n") == 0);
    free(board351782329);
    board351782329 = NULL;
    assert( gamma_move(board, 4, 10, 2) == 0 );
    assert( gamma_move(board, 5, 0, 3) == 0 );
    assert( gamma_move(board, 5, 7, 11) == 0 );
    assert( gamma_move(board, 6, 11, 1) == 0 );
    assert( gamma_free_fields(board, 6) == 21 );
    assert( gamma_golden_move(board, 6, 7, 5) == 0 );


    gamma_delete(board);

    return 0;
}