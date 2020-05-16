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

char* boardWithHighlight(gamma_t* g, uint32_t x, uint32_t y);

/** @brief Czyści terminal.
 * Czyści wyjście terminala.
 */
void clear();

/** @brief Zmienia tryb wejścia.
 * Zmienia tryb wejścia terminala na "raw", wejścia nie trzeba potwierdzać znakiem nowej linii.
 * Ukrywa kursor w terminalu. Zapisuje oryginalne ustawienia terminala w zmiennej globalnej @ref original.
 */
void changeTerminalToRaw();

/** @brief Zmienia tryb wejścia na oryginalny.
 * Przywraca tryb wejścia terminala do tego, sprzed zmiany na "raw". Przywraca widok kursora w terminalu.
 */
void changeTerminalToOriginal();

/** @brief Wypisuje wyniki gry.
 * Wypisuje wyniki gry na jej koniec. W każdej linii zostają wypisane: numer gracza
 * i ile pól zajął w tej grze.
 * @param[in] g – wskaźnik na grę, której wyniki wypisujemy.
 */
void printResults(gamma_t* g);

/** @brief Wypisuje linijkę błędu.
 * Wypisuje numer linii, w której pojawił się błąd w interpretacji poleceń.
 * @param[in] linie – numer linii do wypisania.
 */
void printError(unsigned long long line);

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
 * @param[in] linie   – numer linii, z której zostało wywołane polecenie lub @p 0, jeśli program jest w
 *                      interactive mode.
 */
void printWithHighlight(gamma_t* g, uint32_t x, uint32_t y, unsigned long long line);

/** @brief Wychodzi z trybu interaktywnego.
 * Opuszcza tryb interaktywny. Przywraca terminal do oryginalnych ustawień. Opuszcza program z danym kodem
 * wyjścia.
 * @param[in] code - kod wyjścia, którym ma być zakończony program
 */
void exitInteractive(int code);


#endif //GAMMA_DISPLAY_H
