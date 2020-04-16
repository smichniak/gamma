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
uuid: 183019027
*/
/*
random actions, total chaos
*/
    gamma_t* board = gamma_new(13, 8, 4, 10);
    assert(board != NULL);


    assert(gamma_move(board, 1, 10, 6) == 1);
    assert(gamma_move(board, 2, 7, 4) == 1);
    assert(gamma_move(board, 2, 8, 1) == 1);
    assert(gamma_move(board, 3, 3, 12) == 0);
    assert(gamma_move(board, 3, 12, 4) == 1);
    assert(gamma_move(board, 4, 4, 0) == 1);
    assert(gamma_move(board, 1, 0, 9) == 0);
    assert(gamma_move(board, 2, 1, 5) == 1);
    assert(gamma_move(board, 2, 12, 7) == 1);
    assert(gamma_busy_fields(board, 2) == 4);
    assert(gamma_move(board, 3, 7, 11) == 0);


    char* board140786974 = gamma_board(board);
    assert(board140786974 != NULL);
    assert(strcmp(board140786974,
                  "............2\n"
                  "..........1..\n"
                  ".2...........\n"
                  ".......2....3\n"
                  ".............\n"
                  ".............\n"
                  "........2....\n"
                  "....4........\n") == 0);
    free(board140786974);
    board140786974 = NULL;
    assert(gamma_move(board, 4, 5, 6) == 1);
    assert(gamma_move(board, 4, 10, 6) == 0);
    assert(gamma_golden_possible(board, 4) == 1);
    assert(gamma_move(board, 1, 7, 3) == 1);
    assert(gamma_golden_possible(board, 1) == 1);
    assert(gamma_move(board, 2, 1, 4) == 1);
    assert(gamma_free_fields(board, 2) == 94);
    assert(gamma_move(board, 3, 10, 2) == 1);
    assert(gamma_move(board, 4, 4, 8) == 0);
    assert(gamma_move(board, 1, 4, 11) == 0);
    assert(gamma_move(board, 2, 9, 4) == 1);
    assert(gamma_move(board, 2, 12, 6) == 1);
    assert(gamma_busy_fields(board, 2) == 7);
    assert(gamma_move(board, 3, 7, 2) == 1);


    char* board120794710 = gamma_board(board);
    assert(board120794710 != NULL);
    assert(strcmp(board120794710,
                  "............2\n"
                  ".....4....1.2\n"
                  ".2...........\n"
                  ".2.....2.2..3\n"
                  ".......1.....\n"
                  ".......3..3..\n"
                  "........2....\n"
                  "....4........\n") == 0);
    free(board120794710);
    board120794710 = NULL;
    assert(gamma_move(board, 4, 5, 5) == 1);
    assert(gamma_move(board, 4, 2, 3) == 1);
    assert(gamma_move(board, 1, 9, 3) == 1);
    assert(gamma_move(board, 2, 0, 0) == 1);
    assert(gamma_move(board, 3, 4, 4) == 1);
    assert(gamma_move(board, 4, 3, 6) == 1);
    assert(gamma_move(board, 2, 8, 6) == 1);
    assert(gamma_golden_move(board, 2, 2, 10) == 0);
    assert(gamma_move(board, 3, 12, 4) == 0);
    assert(gamma_move(board, 4, 4, 6) == 1);
    assert(gamma_move(board, 4, 12, 7) == 0);
    assert(gamma_golden_possible(board, 2) == 1);
    assert(gamma_move(board, 3, 3, 2) == 1);
    assert(gamma_move(board, 4, 3, 5) == 1);
    assert(gamma_move(board, 1, 7, 10) == 0);
    assert(gamma_move(board, 2, 6, 4) == 1);
    assert(gamma_move(board, 3, 8, 5) == 1);
    assert(gamma_move(board, 3, 1, 4) == 0);
    assert(gamma_move(board, 4, 11, 3) == 1);
    assert(gamma_move(board, 1, 3, 0) == 1);
    assert(gamma_move(board, 2, 6, 7) == 1);
    assert(gamma_move(board, 2, 5, 2) == 1);
    assert(gamma_busy_fields(board, 2) == 12);
    assert(gamma_move(board, 3, 0, 7) == 1);
    assert(gamma_move(board, 3, 8, 0) == 1);
    assert(gamma_move(board, 4, 4, 0) == 0);
    assert(gamma_move(board, 4, 5, 7) == 1);
    assert(gamma_move(board, 1, 6, 9) == 0);
    assert(gamma_move(board, 1, 2, 4) == 1);
    assert(gamma_free_fields(board, 1) == 70);
    assert(gamma_move(board, 2, 0, 11) == 0);
    assert(gamma_move(board, 2, 11, 4) == 1);
    assert(gamma_move(board, 3, 6, 0) == 1);
    assert(gamma_move(board, 3, 3, 3) == 1);
    assert(gamma_move(board, 4, 0, 2) == 1);
    assert(gamma_move(board, 4, 7, 7) == 1);
    assert(gamma_move(board, 1, 1, 4) == 0);
    assert(gamma_move(board, 1, 4, 7) == 1);
    assert(gamma_move(board, 2, 3, 8) == 0);
    assert(gamma_move(board, 3, 6, 9) == 0);
    assert(gamma_move(board, 4, 6, 9) == 0);
    assert(gamma_move(board, 4, 0, 3) == 1);
    assert(gamma_move(board, 1, 12, 5) == 1);
    assert(gamma_move(board, 1, 4, 7) == 0);
    assert(gamma_move(board, 2, 5, 2) == 0);


    char* board938474275 = gamma_board(board);
    assert(board938474275 != NULL);
    assert(strcmp(board938474275,
                  "3...1424....2\n"
                  "...444..2.1.2\n"
                  ".2.4.4..3...1\n"
                  ".21.3.22.2.23\n"
                  "4.43...1.1.4.\n"
                  "4..3.2.3..3..\n"
                  "........2....\n"
                  "2..14.3.3....\n") == 0);
    free(board938474275);
    board938474275 = NULL;
    assert(gamma_move(board, 3, 5, 6) == 0);
    assert(gamma_golden_possible(board, 3) == 1);
    assert(gamma_move(board, 4, 7, 8) == 0);
    assert(gamma_move(board, 4, 11, 6) == 1);
    assert(gamma_golden_move(board, 4, 3, 9) == 0);
    assert(gamma_move(board, 1, 2, 6) == 1);
    assert(gamma_move(board, 1, 6, 5) == 1);
    assert(gamma_move(board, 2, 5, 7) == 0);
    assert(gamma_move(board, 2, 12, 3) == 0);
    assert(gamma_move(board, 3, 2, 4) == 0);
    assert(gamma_move(board, 3, 1, 7) == 1);
    assert(gamma_move(board, 4, 2, 12) == 0);
    assert(gamma_move(board, 4, 12, 5) == 0);
    assert(gamma_move(board, 1, 5, 4) == 1);
    assert(gamma_move(board, 3, 10, 2) == 0);
    assert(gamma_move(board, 3, 6, 5) == 0);
    assert(gamma_free_fields(board, 3) == 57);
    assert(gamma_move(board, 4, 5, 4) == 0);
    assert(gamma_move(board, 1, 1, 12) == 0);
    assert(gamma_move(board, 2, 6, 6) == 1);
    assert(gamma_move(board, 2, 7, 2) == 0);
    assert(gamma_move(board, 3, 11, 2) == 1);
    assert(gamma_move(board, 3, 9, 0) == 1);
    assert(gamma_move(board, 4, 0, 11) == 0);
    assert(gamma_move(board, 4, 0, 6) == 1);
    assert(gamma_move(board, 1, 5, 10) == 0);
    assert(gamma_move(board, 2, 1, 3) == 1);
    assert(gamma_move(board, 3, 1, 7) == 0);
    assert(gamma_move(board, 3, 2, 4) == 0);
    assert(gamma_golden_move(board, 3, 3, 7) == 0);
    assert(gamma_move(board, 4, 4, 3) == 1);
    assert(gamma_move(board, 1, 0, 3) == 0);
    assert(gamma_busy_fields(board, 1) == 10);
    assert(gamma_golden_possible(board, 1) == 1);
    assert(gamma_golden_possible(board, 2) == 1);
    assert(gamma_move(board, 3, 0, 11) == 0);
    assert(gamma_move(board, 4, 1, 9) == 0);
    assert(gamma_move(board, 2, 3, 6) == 0);
    assert(gamma_move(board, 2, 7, 7) == 0);
    assert(gamma_move(board, 3, 8, 7) == 1);
    assert(gamma_move(board, 4, 11, 2) == 0);
    assert(gamma_move(board, 1, 7, 9) == 0);
    assert(gamma_move(board, 1, 9, 0) == 0);
    assert(gamma_free_fields(board, 2) == 23);
    assert(gamma_move(board, 3, 1, 12) == 0);
    assert(gamma_free_fields(board, 3) == 25);
    assert(gamma_golden_move(board, 3, 6, 2) == 0);


    char* board462402136 = gamma_board(board);
    assert(board462402136 != NULL);
    assert(strcmp(board462402136,
                  "33..14243...2\n"
                  "4.14442.2.142\n"
                  ".2.4.41.3...1\n"
                  ".21.3122.2.23\n"
                  "42434..1.1.4.\n"
                  "4..3.2.3..33.\n"
                  "........2....\n"
                  "2..14.3.33...\n") == 0);
    free(board462402136);
    board462402136 = NULL;
    assert(gamma_move(board, 4, 11, 7) == 1);
    assert(gamma_move(board, 4, 11, 0) == 1);
    assert(gamma_free_fields(board, 4) == 22);
    assert(gamma_golden_move(board, 4, 7, 1) == 0);
    assert(gamma_move(board, 1, 1, 7) == 0);
    assert(gamma_move(board, 2, 1, 4) == 0);
    assert(gamma_move(board, 2, 0, 3) == 0);
    assert(gamma_free_fields(board, 2) == 22);
    assert(gamma_move(board, 3, 7, 2) == 0);
    assert(gamma_move(board, 1, 1, 2) == 0);
    assert(gamma_move(board, 1, 10, 2) == 0);
    assert(gamma_move(board, 2, 2, 6) == 0);
    assert(gamma_move(board, 2, 0, 2) == 0);


    char* board345271224 = gamma_board(board);
    assert(board345271224 != NULL);
    assert(strcmp(board345271224,
                  "33..14243..42\n"
                  "4.14442.2.142\n"
                  ".2.4.41.3...1\n"
                  ".21.3122.2.23\n"
                  "42434..1.1.4.\n"
                  "4..3.2.3..33.\n"
                  "........2....\n"
                  "2..14.3.33.4.\n") == 0);
    free(board345271224);
    board345271224 = NULL;
    assert(gamma_move(board, 3, 0, 12) == 0);
    assert(gamma_move(board, 3, 3, 7) == 0);
    assert(gamma_move(board, 4, 6, 1) == 0);
    assert(gamma_move(board, 4, 11, 6) == 0);
    assert(gamma_move(board, 1, 7, 0) == 0);
    assert(gamma_move(board, 2, 1, 3) == 0);
    assert(gamma_move(board, 2, 11, 0) == 0);
    assert(gamma_move(board, 3, 4, 2) == 1);
    assert(gamma_busy_fields(board, 3) == 15);
    assert(gamma_golden_possible(board, 3) == 1);
    assert(gamma_move(board, 4, 1, 3) == 0);
    assert(gamma_busy_fields(board, 4) == 17);
    assert(gamma_golden_possible(board, 4) == 1);
    assert(gamma_move(board, 1, 1, 2) == 0);
    assert(gamma_move(board, 2, 8, 4) == 1);
    assert(gamma_move(board, 2, 2, 2) == 1);
    assert(gamma_move(board, 3, 2, 6) == 0);
    assert(gamma_move(board, 4, 5, 10) == 0);
    assert(gamma_move(board, 4, 9, 0) == 0);
    assert(gamma_move(board, 1, 1, 9) == 0);
    assert(gamma_move(board, 2, 3, 5) == 0);
    assert(gamma_move(board, 3, 10, 4) == 0);
    assert(gamma_move(board, 4, 0, 1) == 1);
    assert(gamma_move(board, 4, 0, 5) == 1);
    assert(gamma_move(board, 1, 11, 6) == 0);
    assert(gamma_free_fields(board, 1) == 17);
    assert(gamma_move(board, 2, 11, 2) == 0);
    assert(gamma_move(board, 3, 8, 3) == 0);
    assert(gamma_move(board, 4, 2, 12) == 0);
    assert(gamma_move(board, 4, 9, 4) == 0);
    assert(gamma_move(board, 1, 0, 10) == 0);
    assert(gamma_move(board, 1, 6, 7) == 0);
    assert(gamma_move(board, 2, 1, 4) == 0);
    assert(gamma_move(board, 3, 3, 5) == 0);
    assert(gamma_move(board, 3, 11, 7) == 0);
    assert(gamma_move(board, 1, 3, 6) == 0);
    assert(gamma_move(board, 2, 8, 2) == 1);
    assert(gamma_move(board, 2, 11, 3) == 0);
    assert(gamma_move(board, 3, 2, 5) == 0);
    assert(gamma_move(board, 1, 5, 7) == 0);
    assert(gamma_free_fields(board, 1) == 17);
    assert(gamma_move(board, 2, 6, 7) == 0);
    assert(gamma_move(board, 2, 11, 3) == 0);
    assert(gamma_move(board, 3, 2, 0) == 0);
    assert(gamma_free_fields(board, 4) == 19);


    char* board965276446 = gamma_board(board);
    assert(board965276446 != NULL);
    assert(strcmp(board965276446,
                  "33..14243..42\n"
                  "4.14442.2.142\n"
                  "42.4.41.3...1\n"
                  ".21.312222.23\n"
                  "42434..1.1.4.\n"
                  "4.2332.32.33.\n"
                  "4.......2....\n"
                  "2..14.3.33.4.\n") == 0);
    free(board965276446);
    board965276446 = NULL;
    assert(gamma_move(board, 1, 2, 1) == 0);
    assert(gamma_free_fields(board, 1) == 17);
    assert(gamma_move(board, 2, 12, 1) == 0);
    assert(gamma_busy_fields(board, 2) == 18);
    assert(gamma_move(board, 3, 0, 10) == 0);
    assert(gamma_move(board, 4, 10, 1) == 0);
    assert(gamma_move(board, 4, 8, 6) == 0);
    assert(gamma_free_fields(board, 4) == 19);
    assert(gamma_move(board, 1, 3, 10) == 0);
    assert(gamma_move(board, 1, 0, 1) == 0);
    assert(gamma_move(board, 2, 1, 2) == 1);
    assert(gamma_move(board, 3, 9, 7) == 1);
    assert(gamma_free_fields(board, 3) == 23);
    assert(gamma_move(board, 4, 7, 3) == 0);
    assert(gamma_free_fields(board, 4) == 18);
    assert(gamma_move(board, 1, 1, 11) == 0);
    assert(gamma_move(board, 2, 5, 9) == 0);
    assert(gamma_move(board, 2, 2, 6) == 0);
    assert(gamma_move(board, 3, 9, 3) == 0);
    assert(gamma_move(board, 3, 10, 0) == 1);
    assert(gamma_move(board, 4, 5, 7) == 0);
    assert(gamma_move(board, 4, 10, 1) == 0);
    assert(gamma_move(board, 1, 1, 12) == 0);
    assert(gamma_move(board, 1, 11, 1) == 0);
    assert(gamma_move(board, 2, 3, 8) == 0);
    assert(gamma_move(board, 3, 4, 10) == 0);
    assert(gamma_move(board, 4, 2, 12) == 0);
    assert(gamma_move(board, 1, 1, 9) == 0);
    assert(gamma_move(board, 1, 11, 7) == 0);
    assert(gamma_busy_fields(board, 1) == 10);
    assert(gamma_move(board, 2, 3, 5) == 0);
    assert(gamma_move(board, 2, 2, 4) == 0);
    assert(gamma_move(board, 3, 4, 5) == 1);
    assert(gamma_move(board, 3, 6, 5) == 0);
    assert(gamma_move(board, 4, 8, 0) == 0);
    assert(gamma_move(board, 4, 10, 7) == 1);
    assert(gamma_move(board, 2, 3, 8) == 0);
    assert(gamma_move(board, 2, 8, 4) == 0);
    assert(gamma_move(board, 3, 12, 7) == 0);
    assert(gamma_move(board, 4, 1, 4) == 0);
    assert(gamma_move(board, 4, 9, 6) == 0);
    assert(gamma_busy_fields(board, 4) == 20);
    assert(gamma_move(board, 1, 12, 3) == 0);
    assert(gamma_move(board, 1, 3, 5) == 0);
    assert(gamma_golden_possible(board, 1) == 1);
    assert(gamma_move(board, 2, 1, 4) == 0);
    assert(gamma_move(board, 3, 10, 1) == 1);
    assert(gamma_move(board, 3, 5, 4) == 0);
    assert(gamma_busy_fields(board, 3) == 19);
    assert(gamma_free_fields(board, 4) == 15);
    assert(gamma_move(board, 1, 2, 12) == 0);
    assert(gamma_move(board, 1, 4, 5) == 0);
    assert(gamma_golden_possible(board, 1) == 1);
    assert(gamma_move(board, 2, 5, 2) == 0);
    assert(gamma_move(board, 3, 0, 12) == 0);
    assert(gamma_move(board, 3, 1, 7) == 0);
    assert(gamma_move(board, 4, 0, 6) == 0);
    assert(gamma_move(board, 4, 11, 6) == 0);
    assert(gamma_move(board, 1, 2, 9) == 0);
    assert(gamma_move(board, 2, 5, 7) == 0);
    assert(gamma_move(board, 3, 2, 12) == 0);
    assert(gamma_move(board, 3, 11, 4) == 0);
    assert(gamma_move(board, 4, 2, 12) == 0);
    assert(gamma_move(board, 4, 2, 4) == 0);
    assert(gamma_golden_move(board, 4, 7, 9) == 0);
    assert(gamma_move(board, 1, 7, 2) == 0);
    assert(gamma_free_fields(board, 1) == 16);
    assert(gamma_move(board, 2, 0, 3) == 0);
    assert(gamma_move(board, 3, 6, 9) == 0);
    assert(gamma_move(board, 3, 8, 5) == 0);
    assert(gamma_move(board, 4, 1, 11) == 0);
    assert(gamma_move(board, 1, 5, 7) == 0);
    assert(gamma_golden_possible(board, 1) == 1);
    assert(gamma_move(board, 3, 1, 7) == 0);
    assert(gamma_move(board, 3, 3, 4) == 1);
    assert(gamma_move(board, 4, 7, 0) == 0);


    char* board632997535 = gamma_board(board);
    assert(board632997535 != NULL);
    assert(strcmp(board632997535,
                  "33..142433442\n"
                  "4.14442.2.142\n"
                  "42.4341.3...1\n"
                  ".213312222.23\n"
                  "42434..1.1.4.\n"
                  "422332.32.33.\n"
                  "4.......2.3..\n"
                  "2..14.3.3334.\n") == 0);
    free(board632997535);
    board632997535 = NULL;
    assert(gamma_move(board, 1, 0, 12) == 0);


    char* board799309448 = gamma_board(board);
    assert(board799309448 != NULL);
    assert(strcmp(board799309448,
                  "33..142433442\n"
                  "4.14442.2.142\n"
                  "42.4341.3...1\n"
                  ".213312222.23\n"
                  "42434..1.1.4.\n"
                  "422332.32.33.\n"
                  "4.......2.3..\n"
                  "2..14.3.3334.\n") == 0);
    free(board799309448);
    board799309448 = NULL;
    assert(gamma_move(board, 2, 0, 7) == 0);
    assert(gamma_move(board, 2, 5, 4) == 0);
    assert(gamma_busy_fields(board, 2) == 19);
    assert(gamma_move(board, 3, 0, 2) == 0);
    assert(gamma_move(board, 3, 0, 2) == 0);
    assert(gamma_free_fields(board, 3) == 35);
    assert(gamma_move(board, 4, 6, 7) == 0);
    assert(gamma_move(board, 1, 12, 6) == 0);
    assert(gamma_free_fields(board, 1) == 15);
    assert(gamma_move(board, 3, 4, 0) == 0);
    assert(gamma_move(board, 3, 12, 2) == 1);
    assert(gamma_busy_fields(board, 3) == 21);
    assert(gamma_move(board, 4, 1, 3) == 0);
    assert(gamma_move(board, 4, 11, 4) == 0);
    assert(gamma_move(board, 2, 1, 2) == 0);
    assert(gamma_move(board, 3, 1, 5) == 0);
    assert(gamma_busy_fields(board, 3) == 21);
    assert(gamma_golden_move(board, 3, 3, 7) == 0);
    assert(gamma_move(board, 4, 1, 9) == 0);
    assert(gamma_move(board, 1, 1, 11) == 0);
    assert(gamma_move(board, 1, 3, 0) == 0);
    assert(gamma_move(board, 2, 7, 2) == 0);
    assert(gamma_move(board, 4, 6, 7) == 0);
    assert(gamma_move(board, 1, 7, 2) == 0);
    assert(gamma_move(board, 1, 10, 7) == 0);
    assert(gamma_move(board, 2, 1, 1) == 1);
    assert(gamma_move(board, 2, 8, 2) == 0);
    assert(gamma_free_fields(board, 2) == 33);
    assert(gamma_move(board, 3, 1, 2) == 0);
    assert(gamma_move(board, 4, 1, 9) == 0);
    assert(gamma_move(board, 4, 11, 6) == 0);
    assert(gamma_golden_possible(board, 4) == 1);
    assert(gamma_golden_move(board, 4, 3, 3) == 1);
    assert(gamma_move(board, 1, 1, 11) == 0);
    assert(gamma_move(board, 1, 2, 3) == 0);
    assert(gamma_move(board, 2, 2, 9) == 0);
    assert(gamma_move(board, 3, 0, 0) == 0);
    assert(gamma_free_fields(board, 3) == 33);
    assert(gamma_move(board, 4, 1, 6) == 1);
    assert(gamma_move(board, 1, 5, 11) == 0);
    assert(gamma_golden_move(board, 1, 6, 1) == 0);
    assert(gamma_move(board, 2, 12, 6) == 0);
    assert(gamma_move(board, 1, 12, 6) == 0);
    assert(gamma_move(board, 2, 1, 9) == 0);
    assert(gamma_move(board, 3, 4, 0) == 0);
    assert(gamma_move(board, 4, 7, 2) == 0);
    assert(gamma_move(board, 1, 3, 12) == 0);
    assert(gamma_move(board, 1, 1, 5) == 0);
    assert(gamma_busy_fields(board, 1) == 10);
    assert(gamma_move(board, 2, 5, 2) == 0);
    assert(gamma_move(board, 2, 5, 3) == 1);
    assert(gamma_move(board, 3, 3, 10) == 0);
    assert(gamma_move(board, 3, 2, 6) == 0);
    assert(gamma_move(board, 4, 1, 6) == 0);
    assert(gamma_move(board, 4, 2, 5) == 1);
    assert(gamma_move(board, 1, 1, 2) == 0);
    assert(gamma_move(board, 1, 8, 4) == 0);
    assert(gamma_busy_fields(board, 1) == 10);
    assert(gamma_move(board, 2, 4, 3) == 0);
    assert(gamma_golden_possible(board, 2) == 1);
    assert(gamma_golden_move(board, 2, 4, 3) == 1);
    assert(gamma_move(board, 3, 1, 9) == 0);
    assert(gamma_move(board, 3, 6, 0) == 0);
    assert(gamma_move(board, 4, 7, 0) == 1);
    assert(gamma_move(board, 1, 2, 0) == 1);
    assert(gamma_golden_move(board, 1, 2, 5) == 1);
    assert(gamma_busy_fields(board, 2) == 22);


    char* board443120857 = gamma_board(board);
    assert(board443120857 != NULL);
    assert(strcmp(board443120857,
                  "33..142433442\n"
                  "4414442.2.142\n"
                  "4214341.3...1\n"
                  ".213312222.23\n"
                  "424422.1.1.4.\n"
                  "422332.32.333\n"
                  "42......2.3..\n"
                  "2.114.343334.\n") == 0);
    free(board443120857);
    board443120857 = NULL;
    assert(gamma_move(board, 3, 5, 10) == 0);
    assert(gamma_move(board, 3, 1, 3) == 0);
    assert(gamma_golden_possible(board, 3) == 1);
    assert(gamma_move(board, 4, 5, 11) == 0);
    assert(gamma_busy_fields(board, 4) == 22);
    assert(gamma_golden_possible(board, 4) == 0);
    assert(gamma_move(board, 1, 1, 2) == 0);
    assert(gamma_move(board, 2, 4, 0) == 0);
    assert(gamma_move(board, 2, 3, 2) == 0);
    assert(gamma_move(board, 3, 3, 12) == 0);
    assert(gamma_free_fields(board, 3) == 28);
    assert(gamma_move(board, 4, 1, 9) == 0);
    assert(gamma_move(board, 4, 12, 4) == 0);
    assert(gamma_golden_possible(board, 4) == 0);


    char* board560133452 = gamma_board(board);
    assert(board560133452 != NULL);
    assert(strcmp(board560133452,
                  "33..142433442\n"
                  "4414442.2.142\n"
                  "4214341.3...1\n"
                  ".213312222.23\n"
                  "424422.1.1.4.\n"
                  "422332.32.333\n"
                  "42......2.3..\n"
                  "2.114.343334.\n") == 0);
    free(board560133452);
    board560133452 = NULL;
    assert(gamma_move(board, 2, 3, 10) == 0);
    assert(gamma_move(board, 2, 2, 5) == 0);
    assert(gamma_move(board, 3, 0, 12) == 0);
    assert(gamma_move(board, 3, 1, 2) == 0);
    assert(gamma_move(board, 4, 3, 4) == 0);
    assert(gamma_move(board, 4, 6, 5) == 0);
    assert(gamma_free_fields(board, 4) == 11);


    gamma_delete(board);

    return 0;
}