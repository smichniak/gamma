/** @file
 * Interfejs klasy przechowującej stan gry gamma
 *
 * @author Marcin Peczarski <marpe@mimuw.edu.pl>, Szymon Michniak <s.michniak@student.uw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 18.03.2020
 */

#ifndef GAMMA_H
#define GAMMA_H

#include "findUnion.h"

/**
 * @typedef gamma_t
 * Struktura przechowująca stan gry.
 */
typedef struct gamma gamma_t;

/** @brief Zwraca szerokość planszy.
 * Zwraca szerokość planszy w grze opsianej w @p g.
 * @param[in] g   – wskaźnik na strukturę przechowującą stan gry,
 * @return Wartość liczbowa @p uint32_t odpowiadająca szerokości planszy.
 */
uint32_t get_width(gamma_t* g);

/** @brief Zwraca wysokość planszy.
 * Zwraca wysokość planszy w grze opsianej w @p g.
 * @param[in] g   – wskaźnik na strukturę przechowującą stan gry,
 * @return Wartość liczbowa @p uint32_t odpowiadająca wysokości planszy.
 */
uint32_t get_height(gamma_t* g);

/** @brief Zwraca liczbę graczy w grze.
 * Zwraca liczbę graczy w grze opsianej w @p g.
 * @param[in] g   – wskaźnik na strukturę przechowującą stan gry,
 * @return Wartość liczbowa @p uint32_t odpowiadająca liczbie graczy.
 */
uint32_t get_players(gamma_t* g);

/** @brief Zwraca maksymalna liczbę obszarów.
 * Maksymalna liczbę obszarów, które może zająć gracz w grze opsianej w @p g.
 * @param[in] g   – wskaźnik na strukturę przechowującą stan gry,
 * @return Wartość liczbowa @p uint32_t odpowiadająca liczbie obszarów.
 */
uint32_t get_areas(gamma_t* g);

/** @brief Zwraca gracza w wierzchołku o danych współrzędnych.
 * Zwraca gracza w wierzchołku o współrzędnych (@p x, @p y) w grze opsianej w @p g.
 * @param[in] g       – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] x       – numer kolumny, liczba nieujemna mniejsza od wartości
 *                      @p width z funkcji @ref gamma_new,
 * @param[in] y       – numer wiersza, liczba nieujemna mniejsza od wartości
 *                      @p height z funkcji @ref gamma_new.
 * @return Wartość liczbowa @p uint32_t odpowiadająca numerowi gracza.
 */
uint32_t get_player_on_field(gamma_t* g, uint32_t x, uint32_t y);

/** @brief Zwraca liczbę zajętych obszarów.
 * Zwraca liczbę obszarów zajętych przez danego gracza.
 * @param[in] g       – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] player  – numer gracza.
 * @return Wartość liczbowa @p uint32_t odpowiadająca liczbie obszarów.
 */
uint32_t get_player_areas(gamma_t* g, uint32_t player);

/** @brief Tworzy strukturę przechowującą stan gry.
 * Alokuje pamięć na nową strukturę przechowującą stan gry.
 * Inicjuje tę strukturę tak, aby reprezentowała początkowy stan gry.
 * @param[in] width   – szerokość planszy, liczba dodatnia,
 * @param[in] height  – wysokość planszy, liczba dodatnia,
 * @param[in] players – liczba graczy, liczba dodatnia,
 * @param[in] areas   – maksymalna liczba obszarów,
 *                      jakie może zająć jeden gracz, liczba dodatnia.
 * @return Wskaźnik na utworzoną strukturę lub NULL, gdy nie udało się
 * zaalokować pamięci lub któryś z parametrów jest niepoprawny.
 */
gamma_t* gamma_new(uint32_t width, uint32_t height, uint32_t players, uint32_t areas);

/** @brief Usuwa strukturę przechowującą stan gry.
 * Usuwa z pamięci strukturę wskazywaną przez @p g.
 * Nic nie robi, jeśli wskaźnik ten ma wartość NULL.
 * @param[in] g       – wskaźnik na usuwaną strukturę.
 */
void gamma_delete(gamma_t* g);

/** @brief Sprawdza, czy można wykonać ruch na dane pole.
 * Sprawdza, czy gracz @p player może postawić pionek na polu (@p x, @p y).
 * @param[in] g       – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] player  – numer gracza, liczba dodatnia niewiększa od wartości
 *                      @p players z funkcji @ref gamma_new,
 * @param[in] x       – numer kolumny, liczba nieujemna mniejsza od wartości
 *                      @p width z funkcji @ref gamma_new,
 * @param[in] y       – numer wiersza, liczba nieujemna mniejsza od wartości
 *                      @p height z funkcji @ref gamma_new.
 * @return Wartość @p true, jeśli można wykonać ruch, a @p false, gdy ruch
 * jest nielegalny lub któryś z parametrów jest niepoprawny.
 */
bool move_possible(gamma_t* g, uint32_t player, uint32_t x, uint32_t y);

/** @brief Wykonuje ruch.
 * Ustawia pionek gracza @p player na polu (@p x, @p y).
 * @param[in,out] g   – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] player  – numer gracza, liczba dodatnia niewiększa od wartości
 *                      @p players z funkcji @ref gamma_new,
 * @param[in] x       – numer kolumny, liczba nieujemna mniejsza od wartości
 *                      @p width z funkcji @ref gamma_new,
 * @param[in] y       – numer wiersza, liczba nieujemna mniejsza od wartości
 *                      @p height z funkcji @ref gamma_new.
 * @return Wartość @p true, jeśli ruch został wykonany, a @p false,
 * gdy ruch jest nielegalny lub któryś z parametrów jest niepoprawny.
 */
bool gamma_move(gamma_t* g, uint32_t player, uint32_t x, uint32_t y);

/** @brief Wykonuje złoty ruch.
 * Ustawia pionek gracza @p player na polu (@p x, @p y) zajętym przez innego
 * gracza, usuwając pionek innego gracza.
 * @param[in,out] g   – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] player  – numer gracza, liczba dodatnia niewiększa od wartości
 *                      @p players z funkcji @ref gamma_new,
 * @param[in] x       – numer kolumny, liczba nieujemna mniejsza od wartości
 *                      @p width z funkcji @ref gamma_new,
 * @param[in] y       – numer wiersza, liczba nieujemna mniejsza od wartości
 *                      @p height z funkcji @ref gamma_new.
 * @return Wartość @p true, jeśli ruch został wykonany, a @p false,
 * gdy gracz wykorzystał już swój złoty ruch, ruch jest nielegalny
 * lub któryś z parametrów jest niepoprawny.
 */
bool gamma_golden_move(gamma_t* g, uint32_t player, uint32_t x, uint32_t y);

/** @brief Podaje liczbę pól zajętych przez gracza.
 * Podaje liczbę pól zajętych przez gracza @p player.
 * @param[in] g       – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] player  – numer gracza, liczba dodatnia niewiększa od wartości
 *                      @p players z funkcji @ref gamma_new.
 * @return Liczba pól zajętych przez gracza lub zero,
 * jeśli któryś z parametrów jest niepoprawny.
 */
uint64_t gamma_busy_fields(gamma_t* g, uint32_t player);

/** @brief Podaje liczbę pól, jakie jeszcze gracz może zająć.
 * Podaje liczbę wolnych pól, na których w danym stanie gry gracz @p player może
 * postawić swój pionek w następnym ruchu.
 * @param[in] g       – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] player  – numer gracza, liczba dodatnia niewiększa od wartości
 *                      @p players z funkcji @ref gamma_new.
 * @return Liczba pól, jakie jeszcze może zająć gracz lub zero,
 * jeśli któryś z parametrów jest niepoprawny.
 */
uint64_t gamma_free_fields(gamma_t* g, uint32_t player);

/** @brief Sprawdza, czy można wykonać ruch na dane pole.
 * Sprawdza, czy gracz @p player może ustwaić pionek na polu (@p x, @p y)
 * zajętym przez innego gracza.
 * @param[in] g   – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] player  – numer gracza, liczba dodatnia niewiększa od wartości
 *                      @p players z funkcji @ref gamma_new,
 * @param[in] x       – numer kolumny, liczba nieujemna mniejsza od wartości
 *                      @p width z funkcji @ref gamma_new,
 * @param[in] y       – numer wiersza, liczba nieujemna mniejsza od wartości
 *                      @p height z funkcji @ref gamma_new.
 * @return Wartość @p true, jeśli można wykonać złoty ruch, a @p false, gdy ruch
 * jest nielegalny lub któryś z parametrów jest niepoprawny.
 */
bool golden_possible_on_field(gamma_t* g, uint32_t player, uint32_t x, uint32_t y);

/** @brief Sprawdza, czy gracz może wykonać złoty ruch.
 * Sprawdza, czy gracz @p player jeszcze nie wykonał w tej rozgrywce złotego
 * ruchu i jest przynajmniej jedno pole zajęte przez innego gracza, na które
 * można wykonać złoty ruch.
 * @param[in] g       – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] player  – numer gracza, liczba dodatnia niewiększa od wartości
 *                      @p players z funkcji @ref gamma_new.
 * @return Wartość @p true, jeśli gracz jeszcze nie wykonał w tej rozgrywce
 * złotego ruchu i jest przynajmniej jedno pole zajęte przez innego gracza,
 * na które można wykonać złoty ruch, a @p false w przeciwnym przypadku.
 */
bool gamma_golden_possible(gamma_t* g, uint32_t player);

/** @brief Daje napis opisujący stan planszy.
 * Alokuje w pamięci bufor, w którym umieszcza napis zawierający tekstowy
 * opis aktualnego stanu planszy. Przykład znajduje się w pliku gamma_test.c.
 * Funkcja wywołująca musi zwolnić ten bufor.
 * @param[in] g       – wskaźnik na strukturę przechowującą stan gry.
 * @return Wskaźnik na zaalokowany bufor zawierający napis opisujący stan
 * planszy lub NULL, jeśli nie udało się zaalokować pamięci.
 */
char* gamma_board(gamma_t* g);

#endif /* GAMMA_H */
