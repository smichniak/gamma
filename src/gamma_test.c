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
static const char board[] =
        "1.........\n"
        "..........\n"
        "..........\n"
        "......2...\n"
        ".....2....\n"
        "..........\n"
        "..........\n"
        "1.........\n"
        "1221......\n"
        "1.........\n";

/** @brief Testuje silnik gry gamma.
 * Przeprowadza przykładowe testy silnika gry gamma.
 * @return Zero, gdy wszystkie testy przebiegły poprawnie,
 * a w przeciwnym przypadku kod zakończenia programu jest kodem błędu.
 */

int main() {
    // gamma_t* g;

    // g = gamma_new(0, 0, 0, 0);
    //assert(g == NULL);

    // g = gamma_new(3, 2, 10, 3);
    //assert(g != NULL);

    /*  findUnionNode_t elem = make_set(5);
      findUnionNode_t* elemPtr = &elem;
      findUnionNode_t elem2 = make_set(1);
      findUnionNode_t* elemPtr2 = &elem2;
      findUnionNode_t elem3 = make_set(2);
      findUnionNode_t* elemPtr3 = &elem3;
      merge(elemPtr, elemPtr2);

      g->board[1][0] = elemPtr;
      g->board[1][1] = elemPtr2;
      g->board[2][1] = elemPtr3;

      char* boardString = gamma_board(g);
      printf("%s", boardString);
      free(boardString);

      gamma_delete(g);

      printf("%d\n", connected(elemPtr, elemPtr2));
      printf("%d\n", connected(elemPtr, elemPtr3));
      printf("%d\n\n", connected(elemPtr2, elemPtr3));

      printf("%d\n", g->board[1][0] == NULL);
      printf("%d\n", g->board[1][1] == NULL);
      printf("%d\n", g->board[2][1] == NULL);
      printf("%d\n", g->board[2][0] == NULL);
      printf("%d\n\n", g->board[0][0] == NULL);


      uint32_t xd = 0;
      int xd2 = -1;
      printf("%d\n", xd + xd2 < 0);*/

   gamma_t* g;

    g = gamma_new(0, 0, 0, 0);
    assert(g == NULL);

    g = gamma_new(10, 10, 2, 3);
    assert(g != NULL);

    assert(gamma_move(g, 1, 0, 0));
    assert(gamma_busy_fields(g, 1) == 1);
    assert(gamma_busy_fields(g, 2) == 0);
    assert(gamma_free_fields(g, 1) == 99);
    assert(gamma_free_fields(g, 2) == 99);
    assert(!gamma_golden_possible(g, 1));
    assert(gamma_move(g, 2, 3, 1));
    assert(gamma_busy_fields(g, 1) == 1);
    assert(gamma_busy_fields(g, 2) == 1);
    assert(gamma_free_fields(g, 1) == 98);
    assert(gamma_free_fields(g, 2) == 98);
    assert(gamma_move(g, 1, 0, 2));
    assert(gamma_move(g, 1, 0, 9));
    assert(!gamma_move(g, 1, 5, 5));
    assert(gamma_free_fields(g, 1) == 6);
    assert(gamma_move(g, 1, 0, 1));
    assert(gamma_free_fields(g, 1) == 95);
    assert(gamma_move(g, 1, 5, 5));
    assert(!gamma_move(g, 1, 6, 6));
    assert(gamma_busy_fields(g, 1) == 5);
    assert(gamma_free_fields(g, 1) == 10);
    assert(gamma_move(g, 2, 2, 1));
    assert(gamma_move(g, 2, 1, 1));
    assert(gamma_free_fields(g, 1) == 9);
    assert(gamma_free_fields(g, 2) == 92);
    assert(!gamma_move(g, 2, 0, 1));
    assert(gamma_golden_possible(g, 2));
    printf("%s", gamma_board(g));
    assert(!gamma_golden_move(g, 2, 0, 1));
    assert(gamma_golden_move(g, 2, 5, 5));
    assert(!gamma_golden_possible(g, 2));
    assert(gamma_move(g, 2, 6, 6));
    assert(gamma_busy_fields(g, 1) == 4);
    assert(gamma_free_fields(g, 1) == 91);
    assert(gamma_busy_fields(g, 2) == 5);
    assert(gamma_free_fields(g, 2) == 13);
    assert(gamma_golden_move(g, 1, 3, 1));
    assert(gamma_busy_fields(g, 1) == 5);
    assert(gamma_free_fields(g, 1) == 8);
    assert(gamma_busy_fields(g, 2) == 4);
    assert(gamma_free_fields(g, 2) == 10);

    char* p = gamma_board(g);
    assert(p);
    assert(strcmp(p, board) == 0);
    printf("%s", p);
    free(p);

    gamma_delete(g);
    return 0;

    /*   gamma_t* g;

   g = gamma_new(6, 6, 3, 5);
     gamma_move(g, 1, 0, 0);
     gamma_move(g, 1, 0, 1);
     gamma_move(g, 1, 0, 2);
     gamma_move(g, 1, 0, 3);
     gamma_move(g, 1, 0, 4);
     gamma_move(g, 1, 2, 0);
     gamma_move(g, 1, 2, 1);
     gamma_move(g, 1, 2, 2);
     gamma_move(g, 1, 2, 3);
     gamma_move(g, 1, 1, 1);
     printf("%s\n", gamma_board(g)); */


   /* StackNode_t* stackPtr = createStack(1, 3);
    stackPtr = putLast(stackPtr, 2, 4);
    stackPtr = putLast(stackPtr, 3, 5);
    stackPtr = putLast(stackPtr, 4, 6);

    printf("%d\n", getLast(stackPtr).x);
    stackPtr = removeLast(stackPtr);
    printf("%d\n", getLast(stackPtr).x);
    stackPtr = putLast(stackPtr, 5, 6);
    printf("%d\n", getLast(stackPtr).x);

    removeStack(stackPtr); */



}
