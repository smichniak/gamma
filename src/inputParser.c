/** @file
 * Implementacja modułu inputParser.h
 *
 * @author Szymon Michniak <s.michniak@student.uw.edu.pl>
 * @date 17.05.2020
 */

#include <string.h>
#include <ctype.h>
#include <inttypes.h>
#include "display.h"
#include "inputParser.h"

/** Białe znaki, które oddzialają parametry funckji.
 */
static const char WHITE_CHARS[] = " \t\v\f\r";

/** Ciąg znaków, które oznaczją poprawne funkcje i funkcję pustą.
 */
static const char VALID_FUNCTIONS[] = "BImgbfqp ";

/**
 * @struct result_t
 * Struktura przechowująca informacje o wyniku funkcji, która zwraca @p uint64_t.
*/
typedef struct {
    uint64_t resultValue; ///< Wartość, którą funckja zwróciła
    bool valid; ///< @p false, jeśli wywołanie funckji było nieprawidłowe, @p true w przeciwnym przypadku
} result_t;

/** @brief Sprawdza, czy ciąg znaków jest samymi cyframi.
 * Sprawdza, czy każdy znak w ciągu jest cyfrą.
 * @param[in] string   – ciąg znaków do sprawdzenia.
 * @return @p true, jeśli wszystkie znaki są cyframi, @p false w przeciwnym przypadku
 */
static bool onlyDigits(char* string) {
    for (uint32_t i = 0; i < strlen(string); ++i) {
        if (!isdigit(string[i])) {
            return false;
        }
    }
    return true;
}

/** @brief Sprawdza, czy ciąg znaków oznacza poprawną funckję.
 * Sprawdza, czy ciąg znaków jest poprwaną funckją gry @p gamma. Funkcja musi być jednoznakowa, i znak
 * ten musi być jednym z ustalonych w @p VALID_FUNCTIONS.
 * @param[in] function   – ciąg znaków do sprawdzenia.
 * @return @p true, jeśli funckja jest prawidłowa, @p false w przeciwnym przypadku
 */
static bool validFunction(char* function) {
    if (strlen(function) > 1) {
        return false;
    }

    for (uint32_t i = 0; i < strlen(VALID_FUNCTIONS); ++i) {
        if (VALID_FUNCTIONS[i] == function[0]) {
            return true;
        }
    }
    return false;
}

/** @brief Sprawdza, czy ciąg znaków oznacza poprawnym argumentem funkcji.
 * Sprawdza, czy ciąg znaków jest argumentem funkcji gry @p gamma. Argument musi zawierać jednynie
 * cryfry i dać się poprawnie skonwertować na typ @p uint32_t. Jeśli @p string jest równy @p NULL,
 * to argument jest pusty.
 * @param[in] string   – ciąg znaków do sprawdzenia.
 * @return Struktura opisująca argument funkcji.
 */
static argument_t validArgument(char* string) {
    argument_t argument;
    argument.value = 0;
    argument.valid = true;
    argument.empty = false;

    if (string == NULL) {
        argument.empty = true;
    } else if (!onlyDigits(string)) {
        //Argument może zawierać tylko cyfry, żeby był poprawny
        argument.valid = false;
    } else {
        uint64_t conversion = strtoul(string, NULL, 10);
        if (conversion > UINT32_MAX) {
            //Wynik większy od UINT32_MAX nie jest poprawny
            argument.valid = false;
        } else {
            argument.value = conversion;
        }

    }

    return argument;
}

/** @brief Wskazuje następnego gracza, który może wykonać ruch.
 * Sprawdza kolejych gracz po @p currentPlayer. Zwraca następnego, który może wykonać ruch. Jeśli
 * liczba pominiętych graczy jest większa, niż liczba wszystkich graczy, to nikt nie może już wykonać
 * ruchu.
 * @param[in] g              – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] currentPlayer  – numer gracza, którego tura się skończyła, liczba dodatnia niewiększa od wartości
 *                              @p players z funkcji @ref gamma_new,
 * @param[in] playersSkipped – liczba pominiętych graczy, przy pierwszym wywołaniu zawsze wynosi 0
 * @return Numer następnego gracza, który może wykonać ruch, lub @p 0 jeśli żaden gracz nie może już
 * wykonać ruchu.
 */
static uint32_t getNextPlayer(gamma_t* g, uint32_t currentPlayer, uint64_t playersSkipped) {
    //Jeśli sprawdziliśmy wszytskich graczy i żaden nie może wykonać ruchu, to zwracamy 0
    if (playersSkipped > get_players(g)) {
        return 0;
    }
    uint32_t maxPlayer = get_players(g);
    //Po ostatnim graczu wracamy do nr 1
    uint32_t nextPlayer = (currentPlayer % maxPlayer) + 1;

    //Jeśli aktualny gracz nie może wykonać ruchu, sprawdzamy następnego
    if (gamma_free_fields(g, nextPlayer) == 0 && !gamma_golden_possible(g, nextPlayer)) {
        return getNextPlayer(g, nextPlayer, playersSkipped + 1);
    }
    return nextPlayer;
}

/** @brief Interpretuje wejście trybu interaktywnego.
 * Ustawia tryb wejścia na "raw", zaczyna od gracza nr 1 i ustawia wskaźnik na pole (0, 0). Wywołuje
 * funkcje w zależności od wejścia zgodnie ze specyfikacją gry gamma. Przerywa po wykryciu na wejściu
 * znaku o kodzie 4 (ctrl + D) lub gdy żaden gracz nie może wykonać ruchu. Wypisuje podsumowanie gry i
 * przywraca oryginalne ustawienia terminala.
 * @param[in,out] g – wskaźnik na strukturę przechowującą stan gry.
 */
static void interactiveInput(gamma_t* g) {
    uint32_t cursorX = 0;
    uint32_t cursorY = 0;
    uint32_t maxX = get_width(g) - 1;
    uint32_t maxY = get_height(g) - 1;
    uint32_t currentPlayer = 1;
    bool nextPlayer;
    int inputCharacter = 0;

    changeTerminalToRaw();

    while (currentPlayer != 0) {
        nextPlayer = false;

        clear();
        printWithHighlight(g, cursorX, cursorY, 0);
        printPlayerInfo(g, currentPlayer);

        //inputCharacter == 0 wtedy, gdy poprzedni wczytany znak został już zinterpretowany
        if (inputCharacter == 0) {
            inputCharacter = getchar();
        }

        if (inputCharacter == '\033') { //Początek kodu strzałek
            inputCharacter = getchar();
            if (inputCharacter == '[') {
                inputCharacter = getchar();
                if (inputCharacter == 'A') { //Strzałak w górę
                    if (cursorY != maxY) {
                        cursorY++;
                    }
                    inputCharacter = 0;
                } else if (inputCharacter == 'B') { //Strzałka w dół
                    if (cursorY != 0) {
                        cursorY--;
                    }
                    inputCharacter = 0;
                } else if (inputCharacter == 'C') { //Strzałka w prawo
                    if (cursorX != maxX) {
                        cursorX++;
                    }
                    inputCharacter = 0;
                } else if (inputCharacter == 'D') { //Strzałka w lewo
                    if (cursorX != 0) {
                        cursorX--;
                    }
                    inputCharacter = 0;
                }
            }
        } else if (inputCharacter == ' ') {
            nextPlayer = gamma_move(g, currentPlayer, cursorX, cursorY);
            inputCharacter = 0;
        } else if (inputCharacter == 'g' || inputCharacter == 'G') {
            nextPlayer = gamma_golden_move(g, currentPlayer, cursorX, cursorY);
            inputCharacter = 0;
        } else if (inputCharacter == 'c' || inputCharacter == 'C') {
            inputCharacter = 0;
            nextPlayer = true;
        } else if (inputCharacter == 4) { //Koniec transmisji, gracz = 0 kończy tryb interaktywny
            currentPlayer = 0;
        } else { //Znak, który nie odpowiada żadnaje komendzie
            inputCharacter = 0;
        }

        if (nextPlayer) {
            currentPlayer = getNextPlayer(g, currentPlayer, 0);
        }
    }

    //Na koniec gry wypisujemy planszę i podsumowanie wyników
    clear();
    printWithHighlight(g, UINT32_MAX, UINT32_MAX, 0);
    printResults(g);
    exitInteractive(0);
}

/** @brief Zwraca domyślną komendę.
 * Zwraca strukturę domyślnej komendy. Jest ona poprawna, ma puste argumenty i nie powoduje żadnego działania.
 * @return Struktura opisująca domyślną komendę.
 */
static command_t defCommand() {
    command_t command;
    command.function = ' ';
    command.isValid = true;
    command.firstArgument = validArgument("");
    command.secondArgument = validArgument("");
    command.thirdArgument = validArgument("");
    command.fourthArgument = validArgument("");
    return command;
}

command_t getCommand(char* line) {
    command_t command = defCommand();

    //Pomijamy linie puste i zaczynajace się od #
    if (line != NULL && line[0] != '#' && line[0] != '\n') {
        if (strlen(line) == 0 || isspace(line[0]) || line[strlen(line) - 1] != '\n') {
            //Błędne są linie nie kończące się znakiem nowej linii i rozpoczynające się białym znakiem
            command.isValid = false;
        } else {
            //Usuwamy '\n' z końca linii
            line[strlen(line) - 1] = 0;

            //Rozdzielamy części miedzy białymi znakami
            char* function = strtok(line, WHITE_CHARS);

            char* firstArg = strtok(NULL, WHITE_CHARS);
            argument_t firstArgument = validArgument(firstArg);

            char* secondArg = strtok(NULL, WHITE_CHARS);
            argument_t secondArgument = validArgument(secondArg);

            char* thirdArg = strtok(NULL, WHITE_CHARS);
            argument_t thirdArgument = validArgument(thirdArg);

            char* fourthArg = strtok(NULL, WHITE_CHARS);
            argument_t fourthArgument = validArgument(fourthArg);

            char* restOfLine = strtok(NULL, WHITE_CHARS);

            if (function != NULL) {
                if (restOfLine != NULL || !validFunction(function) || !firstArgument.valid ||
                    !secondArgument.valid || !thirdArgument.valid || !fourthArgument.valid) {
                    //Prawidłowa linia nie może mieć więcej niż 4 argumenty i każdy musi być poprawny
                    command.isValid = false;
                } else {
                    command.function = function[0];
                    command.firstArgument = firstArgument;
                    command.secondArgument = secondArgument;
                    command.thirdArgument = thirdArgument;
                    command.fourthArgument = fourthArgument;
                }
            }
        }
    }


    return command;
}

/** @brief Wywołuje daną komendę w grze danej wskaźnikiem.
 * Wywołuje jedną z funkcji {@p m, @p g, @p b, @p f, @p q} i wynik wywołania zapisuje w strukturze, która
 * jest zwracana.
 * @param[in,out] gPtr   – wskaźnik na wskaźnik na strukturę przechowującą stan gry,
 * @param[in] command    – struktura opisująca komendę do wywoałnia.
 * @return Struktura opisująca wynik wywołania. Parametr poprawności ustawiony na @p true, jeśli udało się
 * wyowałać funkcję, @p false w przeciwnym przypadku.
 */
static result_t functionResult(gamma_t** gPtr, command_t command) {
    result_t result;
    result.valid = true;

    if (!command.fourthArgument.empty || !*gPtr) {
        result.valid = false;
    } else if (command.function == 'm') { //Zwykly ruch, trzy argumenty
        if (command.thirdArgument.empty) {
            result.valid = false;
        } else {
            result.resultValue = gamma_move(*gPtr, command.firstArgument.value, command.secondArgument.value,
                                            command.thirdArgument.value);
        }
    } else if (command.function == 'g') { //Złoty ruch, trzy argumenty
        if (command.thirdArgument.empty) {
            result.valid = false;
        } else {
            result.resultValue = gamma_golden_move(*gPtr, command.firstArgument.value,
                                                   command.secondArgument.value, command.thirdArgument.value);
        }
    } else if (!command.secondArgument.empty || command.firstArgument.empty) {
        result.valid = false;
    } else if (command.function == 'b') { //Zajęte pola, jeden argument
        result.resultValue = gamma_busy_fields(*gPtr, command.firstArgument.value);
    } else if (command.function == 'f') { //Wolne pola, jeden argument
        result.resultValue = gamma_free_fields(*gPtr, command.firstArgument.value);
    } else if (command.function == 'q') { //Czy możliwy złoty ruch, jeden argument
        result.resultValue = gamma_golden_possible(*gPtr, command.firstArgument.value);
    }

    return result;
}

void executeCommand(command_t command, gamma_t** gPtr, unsigned long long line) {
    if (!command.isValid) {
        printError(line);
    } else if (command.function == ' ') { //Pusta komenda, nic nie robi
    } else if (command.function == 'B' || command.function == 'I') {
        if (*gPtr) { //Nie możemy zacząć nowej gry, jeśli już jakaś trwa
            printError(line);
        } else {
            gamma_t* new_gamma = gamma_new(command.firstArgument.value, command.secondArgument.value,
                                           command.thirdArgument.value, command.fourthArgument.value);
            if (!new_gamma) { //Błędne argumenty lub problemy z alokacją nowej gry
                printError(line);
            } else if (command.function == 'B') {
                *gPtr = new_gamma;
                printf("OK %llu\n", line);
            } else {
                interactiveInput(new_gamma);
            }
        }

    } else if (command.function == 'p') { //Ciąg znaków opisujący planszę, zero argumentów
        if (!command.firstArgument.empty) {
            printError(line);
        } else {
            //x i y = UINT32_MAX oznaczają string planszy bez podświetlonych pól
            printWithHighlight(*gPtr, UINT32_MAX, UINT32_MAX, line);
        }

    } else {
        result_t result = functionResult(gPtr, command);
        if (!result.valid) {
            printError(line);
        } else {
            printf("%" PRIu64 "\n", result.resultValue);
        }
    }
}