/** @file
 * Interfejs modułu, który odpowiada za wypisywanie wyjścia.
 *
 * @author Szymon Michniak <s.michniak@student.uw.edu.pl>
 * @date 16.05.2020
 */

#ifndef GAMMA_DISPLAY_H
#define GAMMA_DISPLAY_H

#include "gamma.h"
#include <unistd.h>
#include <termios.h>

/** @brief Czyści terminal.
 * Czyści wyjście terminala.
 */
void clear();

/** @brief Zmienia tryb wejścia.
 * Zmienia tryb wejścia terminala na "raw", wejścia nie trzeba potwierdzać znakiem nowej linii.
 * Ukrywa kursor w terminalu. Zapisuje oryginalne ustawienia terminala w zmiennej globalnej @ref original.
 */
void change_terminal_to_raw();

/** @brief Zmienia tryb wejścia na oryginalny.
 * Przywraca tryb wejścia terminala do tego, sprzed zmiany na "raw". Przywraca widok kursora w terminalu.
 */
void change_terminal_to_original();

/** @brief Wychodzi z trybu interaktywnego.
 * Opuszcza tryb interaktywny. Przywraca terminal do oryginalnych ustawień. Opuszcza program z danym kodem
 * wyjścia.
 * @param[in] code - kod wyjścia, którym ma być zakończony program
 */
void exit_interactive(int code);

/** @brief Daje napis opisujący stan planszy z opcjonalnym podświetleniem.
 * Alokuje w pamięci bufor, w którym umieszcza napis zawierający tekstowy opis aktualnego stanu planszy.
 * Funkcja wywołująca musi zwolnić ten bufor.
 * Jeśli @p current_player > 0, zaznacza podświetleniem pole o współrzędnych (@p x, @p y) na kolor odpowiadający
 * możliwości ruchu danego gracza na to pole.
 * @param[in] g       – wskaźnik na strukturę przechowującą stan gry.
 * @param[in] x       – numer kolumny pola do podświetlenia, liczba nieujemna mniejsza od wartości
 *                      @p width z funkcji @ref gamma_new,
 * @param[in] y       – numer wiersza pola do podświetlenia, liczba nieujemna mniejsza od wartości
 *                      @p height z funkcji @ref gamma_new.
 * @param[in] current_player  – numer gracza, liczba dodatnia niewiększa od wartości @p players z funkcji @ref gamma_new.
 * @return Wskaźnik na zaalokowany bufor zawierający napis opisujący stan planszy lub NULL, jeśli nie
 * udało się zaalokować pamięci.
 */
char* board_with_highlight(gamma_t* g, uint32_t x, uint32_t y, uint32_t current_player);

/** @brief Wypisuje napis opisujący stan planszy.
 * Wypisuje napis opisujący aktualny stan planszy.
 * Jeśli @p x < UINT32_MAX, zaznacza podświetleniem pole o współrzeędnych (@p x, @p y).
 * Jeśli nie udało się zaalokować pamięci na napis, wypisuje komunikat o błędzie w linii @p line,
 * lub kończy program z kodem błędy @p 1, jeśli @p line jest równe 0 (oznacza to, że opuszczamy
 * interactive mode).
 * @param[in] g       – wskaźnik na strukturę przechowującą stan gry.
 * @param[in] x       – numer kolumny pola do podświetlenia, liczba nieujemna mniejsza od wartości
 *                      @p width z funkcji @ref gamma_new,
 * @param[in] y       – numer wiersza pola do podświetlenia, liczba nieujemna mniejsza od wartości
 *                      @p height z funkcji @ref gamma_new.
 * @param[in] line   – numer linii, z której zostało wywołane polecenie lub @p 0, jeśli program jest w
 *                      interactive mode.
 * @param[in] current_player  – numer gracza, liczba dodatnia niewiększa od wartości @p players z funkcji @ref gamma_new.
 */
void print_with_highlight(gamma_t* g, uint32_t x, uint32_t y, unsigned long long line, uint32_t current_player);

/** @brief Wypisuje wyniki gry.
 * Wypisuje wyniki gry na jej koniec. W każdej linii zostają wypisane: numer gracza
 * i ile pól zajął w tej grze.
 * @param[in] g – wskaźnik na grę, której wyniki wypisujemy.
 */
void print_results(gamma_t* g);

/** @brief Wypisuje linijkę błędu.
 * Wypisuje numer linii, w której pojawił się błąd w interpretacji poleceń.
 * @param[in] line – numer linii do wypisania.
 */
void print_error(unsigned long long line);

/** @brief Wypisuje informacje o graczu.
 * Wypisuje informacje o danym graczu - liczba zajętych obszarów, pól, wolnych pól i czy może wykonać złoty ruch.
 * @param[in] g       – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] player  – numer gracza, liczba dodatnia niewiększa od wartości @p players z funkcji @ref gamma_new.
 */
void print_player_info(gamma_t* g, uint32_t player);


#endif /* GAMMA_DISPLAY_H */
