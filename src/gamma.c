/** @file
 * Implementacja modułu gamma.h
 *
 * @author Szymon Michniak <s.michniak@student.uw.edu.pl>
 * @date 16.04.2020
 */

#include "gamma.h"
#include "display.h"
#include "findUnion.h"
#include <string.h>

/** @struct gamma
 * Struktura przechowująca stan gry.
 */
struct gamma {
    uint32_t width; ///< Szerokość planszy, liczba dodatnia
    uint32_t height; ///< Wysokość planszy, liczba dodatnia
    uint32_t players; ///< Liczba graczy, liczba dodatnia
    uint32_t areas; ///< Maksymalna liczba obszarów, jakie może zająć jeden gracz, liczba dodatnia
    uint64_t free_fields; ///< Wolne pola na planszy, liczba nieujemna
    uint64_t* busy_fields; ///< Tablica liczby pól zajętych przez danego gracza, indeksowana numerami graczy
    uint64_t* free_adjacent_fields; ///< Tablica wolnych pól wokół danego gracza, indeksowana numerami graczy
    uint32_t* player_areas; ///< Tablica zajętych obszarów przez danego gracza, indeksowana numerami graczy
    bool* golden_moves; /**< Tablica wartości logicznych, @p false dla gracza, który jeszcze nie wykonał złotego
                            ruchu, @p true w przeciwnym przyapdku, indeksowana numerami graczy */
    find_union_node_t*** board; /**< Dwuwymiarowa tablica planszy, w każdym zajętym polu wskaźnik na wierzchołek
                                   drzewa Find-Union obszaru, indeksowana współrzędnymi pola */
};

uint32_t get_width(gamma_t* g) {
    return g->width;
}

uint32_t get_height(gamma_t* g) {
    return g->height;
}

uint32_t get_players(gamma_t* g) {
    return g->players;
}

uint32_t get_areas(gamma_t* g) {
    return g->areas;
}

uint32_t get_player_areas(gamma_t* g, uint32_t player) {
    return g->player_areas[player];
}

uint32_t get_player_on_field(gamma_t* g, uint32_t x, uint32_t y) {
    return get_player(g->board[x][y]);
}

/** @brief Sprawdza poprawność współrzędnych.
 * Sprawdza, czy współrzędne @p x i @p y są poprawne dla planszy @p g.
 * @param[in] g       – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] x       – numer kolumny, liczba nieujemna mniejsza od wartości
 *                      @p width z funkcji @ref gamma_new,
 * @param[in] y       – numer wiersza, liczba nieujemna mniejsza od wartości
 *                      @p height z funkcji @ref gamma_new.
 * @return Wartość @p true, dla poprawnych współrzędnych, a @p false
 * w przeciwnym przypadku.
 */
static inline bool valid_coordinates(gamma_t* g, uint32_t x, uint32_t y) {
    return x < g->width && y < g->height;
}

/** @brief Sprawdza poprawność współrzędnych.
 * Sprawdza, czy gracz @p player jest poprawny dla planszy @p g.
 * @param[in] g       – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] player  – numer gracza, liczba dodatnia niewiększa od wartości
 *                      @p players z funkcji @ref gamma_new.
 * @return Wartość @p true, dla poprawnego gracza, a @p false
 * w przeciwnym przypadku.
 */
static inline bool valid_player(gamma_t* g, uint32_t player) {
    return player >= 1 && player <= g->players;
}

/** @brief Alokuje pamięć na potrzebne tablice.
 * Alokuje pamięć na tablice potrzebne do stworzenia gry i wyniki alokacji
 * przypisuje na odpowiednie miejsca w strukturze.
 * @param[in,out] g – wskaźnik na strukturę przechowującą stan gry.
 */
static void alloc_arrays(gamma_t* g) {
    // Rzutowanie na uint64_t, ponieważ dla players = UINT32_MAX, players + 1 = 0
    g->busy_fields = calloc((uint64_t) g->players + 1, sizeof(uint64_t));
    g->free_adjacent_fields = calloc((uint64_t) g->players + 1, sizeof(uint64_t));
    g->player_areas = calloc((uint64_t) g->players + 1, sizeof(uint32_t));
    g->golden_moves = calloc((uint64_t) g->players + 1, sizeof(bool));
    g->board = calloc((uint64_t) g->width * ((uint64_t) g->height + 1), sizeof(find_union_node_t*));
}

/** @brief Tworzy tablicę dwuwymiarową.
 * Odpowiednio ustawia wskaźniki, tak by stworzyć tablicę dwuwymiarową,
 * która będzie reprezentować planszę.
 * @param[in,out] g – wskaźnik na strukturę przechowującą stan gry,
 */
static void setup_board(gamma_t* g) {
    // Wskaźnik kolumny wskazuje na pierwszy element w tablicy 2D
    find_union_node_t** column_ptr = (find_union_node_t**) (g->board + g->width);

    // Dla każdej kolumny ustawiamy jej wskaźnik na prawidłowe miejsce
    for (uint32_t i = 0; i < g->width; ++i) {
        g->board[i] = (column_ptr + g->height * i);
    }
}

gamma_t* gamma_new(uint32_t width, uint32_t height, uint32_t players, uint32_t areas) {
    if (width < 1 || height < 1 || players < 1 || areas < 1) {
        return NULL;
    }
    gamma_t* new_gamma_ptr = calloc(1, sizeof(gamma_t));
    if (!new_gamma_ptr) {
        return NULL;
    }

    new_gamma_ptr->width = width;
    new_gamma_ptr->height = height;
    new_gamma_ptr->players = players;
    new_gamma_ptr->areas = areas;
    new_gamma_ptr->free_fields = width * height;

    alloc_arrays(new_gamma_ptr);

    if (new_gamma_ptr->board) {
        setup_board(new_gamma_ptr);
    }

    if (!new_gamma_ptr->busy_fields || !new_gamma_ptr->free_adjacent_fields || !new_gamma_ptr->player_areas ||
        !new_gamma_ptr->golden_moves || !new_gamma_ptr->board) {
        gamma_delete(new_gamma_ptr);
        return NULL;
    }

    return new_gamma_ptr;
}

void gamma_delete(gamma_t* g) {
    if (g) {
        if (g->board) {
            for (uint32_t x = 0; x < g->width; ++x) {
                for (uint32_t y = 0; y < g->height; ++y) {
                    free(g->board[x][y]);
                }
            }
        }
        free(g->busy_fields);
        free(g->free_adjacent_fields);
        free(g->player_areas);
        free(g->golden_moves);
        free(g->board);
        free(g);
    }
}

/** @brief Zwraca pola sąsiednie do danego.
 * Zwraca tablicę par ze współrzędnymi sąsiednich pól.
 * @param[in] g       – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] x       – numer kolumny, liczba nieujemna mniejsza od wartości
 *                      @p width z funkcji @ref gamma_new,
 * @param[in] y       – numer wiersza, liczba nieujemna mniejsza od wartości
 *                      @p height z funkcji @ref gamma_new.
 * @return Wskaźnik na pierwszy element tablicy lub NULL, gdy nie udało się
 * zaalokować pamięci.
 */
static tuple* get_adjacent(gamma_t* g, uint32_t x, uint32_t y) {
    tuple* adjacent;
    // Są 4 sąsiedznie pola
    adjacent = calloc(4, sizeof(tuple));
    if (!adjacent) {
        return NULL;
    }
    int index = 0;

    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if ((dx + dy) % 2 != 0) {
                if (valid_coordinates(g, x + dx, y + dy)) {
                    adjacent[index] = create_tuple(x + dx, y + dy);
                } else {
                    // Pole poza granicami planszy oznaczamy przez UINT32_MAX
                    // Normalnie pole nigdy nie ma takich współrzędnych
                    adjacent[index] = create_tuple(UINT32_MAX, UINT32_MAX);
                }
                index++;
            }
        }
    }
    return adjacent;
}

/** @brief Sprawdza, czy w sąsiedztwie danego pola jest pole z danym graczem.
 * Przegląda tablicę pól @p adjacent i sprawdza, które mają w sobie gracza @p player.
 * @param[in] g       – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] player  – numer gracza, liczba dodatnia niewiększa od wartości
 *                      @p players z funkcji @ref gamma_new,
 * @param[in] adjacent - maksymalnie czteroelementowa tablica par współrzędnych @p x i @p y
 * @return @p true, jeśli w sąsiedztwie jest pole z graczem @p player, @p false w przeciwnym przypadku.
 */
static bool adjacent_with_player(gamma_t* g, uint32_t player, tuple* adjacent) {
    for (int i = 0; i < 4; ++i) {
        uint32_t x2 = adjacent[i].x;
        uint32_t y2 = adjacent[i].y;
        if (valid_coordinates(g, x2, y2) && get_player(g->board[x2][y2]) == player) {
            return true;
        }
    }
    return false;
}

/** @brief Zwraca liczbę nowych, pustych sąsiednich pól.
 * Przegląda tablicę pól @p adjacent i zlicza puste pola, które nie sąsiadują
 * z zajętym polem z podanym graczem.
 * @param[in] g       – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] player  – numer gracza, liczba dodatnia niewiększa od wartości
 *                      @p players z funkcji @ref gamma_new,
 * @param[in] adjacent - maksymalnie czteroelementowa tablica par współrzędnych @p x i @p y
 * @return Liczba ze zbioru {0, 1, 2, 3, 4}, liczba wolnych sąsiednich pól z danym graczem lub -1 gdy
 * wystąpił błąd alokacji pamięci.
 */
static int new_free_adjacent(gamma_t* g, uint32_t player, tuple* adjacent) {
    int free_adjacent = 0;
    for (int i = 0; i < 4; ++i) {
        uint32_t x2 = adjacent[i].x;
        uint32_t y2 = adjacent[i].y;
        if (valid_coordinates(g, x2, y2) && !g->board[x2][y2]) {
            free_adjacent++;
            tuple* adjacent_to2 = get_adjacent(g, x2, y2);
            if (!adjacent_to2) {
                return -1;
            }
            if (adjacent_with_player(g, player, adjacent_to2)) {
                // Odejmujemy pola, które już są policzone, jako wolne i sąsiadujące z danym graczem
                free_adjacent--;
            }
            free(adjacent_to2);
        }
    }
    return free_adjacent;
}

/** @brief Zwraca liczbę nowych obszarów po zwykłym ruchu.
 * Przegląda tablicę pól @p adjacent i zlicza pola zajęte przez gracza @p player,
 * które po położeniu pionka łączą się w jeden obszar.
 * @param[in, out] g         – wskaźnik na strukturę przechowującą stan gry,
 * @param[in, out] field     – pole, na którym stawiamy pionek, element @p g,
 * @param[in, out] adjacent  - maksymalnie czteroelementowa tablica par współrzędnych @p x i @p y
 * @return Liczba ze zbioru {-3, -2, -1, 0, 1}, o ile zmienia się liczba obszarów zajętych przez gracza.
 */
static int new_areas_move(gamma_t* g, find_union_node_t* field, tuple* adjacent) {
    // Nowy pionek może statnowić jeden, nowy obszar
    int new_area = 1;
    for (int i = 0; i < 4; ++i) {
        uint32_t x2 = adjacent[i].x;
        uint32_t y2 = adjacent[i].y;
        if (valid_coordinates(g, x2, y2) && get_player(g->board[x2][y2]) == get_player(field) &&
            !connected(field, g->board[x2][y2])) {

            unite(field, g->board[x2][y2]);
            // Nowych obszarów jest mniej, jeśli dołączamy się do już istniejacych
            new_area--;
        }
    }
    return new_area;
}

/** @brief Aktualizuje liczbę wolnych pól.
 * Przegląda tablicę pól @p adjacent i dla każdego pola aktualizuje liczbę wolnych pół, wokoł tego pola.
 * Każdego gracza zliczamy tylko raz. Przy położeniu nowego pionka zmniejszamy liczbę wolnych pól o 1, a
 * gdy usuwamy pionek, zwiększamy.
 * @param[in, out] g           – wskaźnik na strukturę przechowującą stan gry,
 * @param[in, out] adjacent    - maksymalnie czteroelementowa tablica par współrzędnych @p x i @p y
 * @param[in] to_add            - @p -1 lub @p 1
 */
static void update_adjacent_free(gamma_t* g, tuple* adjacent, int to_add) {
    uint32_t already_counted[4] = {0, 0, 0, 0};
    for (int i = 0; i < 4; ++i) {
        uint32_t x2 = adjacent[i].x;
        uint32_t y2 = adjacent[i].y;
        if (valid_coordinates(g, x2, y2)) {
            bool counted = false;
            for (int j = 0; j < i; ++j) {
                counted = counted || get_player(g->board[x2][y2]) == already_counted[j];
            }
            if (g->board[x2][y2] && !counted) {
                g->free_adjacent_fields[get_player(g->board[x2][y2])] += to_add;
                already_counted[i] = get_player(g->board[x2][y2]);
            }
        }
    }
}

bool move_possible(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
    if (!g || !valid_player(g, player) || !valid_coordinates(g, x, y) || g->board[x][y]) {
        return false;
    }

    if (g->player_areas[player] < g->areas) {
        return true;
    }

    tuple* adjacent = get_adjacent(g, x, y);
    if (!adjacent) {
        return false;
    }

    bool same_player_adjacent = adjacent_with_player(g, player, adjacent);
    free(adjacent);
    return same_player_adjacent;
}

bool gamma_move(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
    if (!move_possible(g, player, x, y)) {
        return false;
    }
    tuple* adjacent = get_adjacent(g, x, y);
    find_union_node_t* field = make_set(player);
    if (!adjacent || !field) {
        free(adjacent);
        free(field);
        return false;
    }
    int free_adjacent = new_free_adjacent(g, player, adjacent);

    // Stawiamy nowy pionek, zmniejszamy o 1 wolne pola
    update_adjacent_free(g, adjacent, -1);

    g->busy_fields[player]++;
    g->player_areas[player] += new_areas_move(g, field, adjacent);
    g->free_adjacent_fields[player] += free_adjacent;
    g->board[x][y] = field;
    g->free_fields--;

    free(adjacent);
    return true;
}

/** @brief Wykonuje algorytm dfs na polach połączonych z polem wejściowym
 * Po usunięciu pionka przechodzi pola połączone z nim i umieszcza w nich nowe wskaźniki na wierzchołki
 * Find-Union, które nie są połączone z usuniętym pionkiem. Stare pola do zwolnienia później umieszcza
 * w tablicy, na którą wskazuje @p old_fields.
 * @param[in,out] g          – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] x              – numer kolumny, liczba nieujemna mniejsza od wartości
 *                             @p width z funkcji @ref gamma_new,
 * @param[in] y              – numer wiersza, liczba nieujemna mniejsza od wartości
 *                             @p height z funkcji @ref gamma_new,
 * @param[in, out] old_fields - wskaźnik na pierwszy element tablicy wskaźników na pola,
 * @param[in, out] old_fields_index_ptr - wskaźnik na indeks pierwszego wolnego miejsca w tablicy
 * @p old_fields.
 * @return Wartość @p true, jeśli pomyślnie wykonano dfs dla wszytskich potrzebnych pól, @p false
 * w przypadku problemów z pamięcią.
 */
static bool dfs(gamma_t* g, uint32_t x, uint32_t y, find_union_node_t** old_fields, uint64_t* old_fields_index_ptr) {
    if (!g->board[x][y]) {
        return true;
    }
    uint32_t player = get_player(g->board[x][y]);
    stack_node_t* stack_ptr = create_stack(x, y);

    if (!stack_ptr) {
        return false;
    }

    while (!is_stack_empty(stack_ptr)) {
        uint32_t current_x = get_last(stack_ptr).x;
        uint32_t current_y = get_last(stack_ptr).y;
        stack_ptr = remove_last(stack_ptr);

        tuple* adjacent = get_adjacent(g, current_x, current_y);
        if (!adjacent) {
            remove_stack(stack_ptr);
            return false;
        }

        find_union_node_t* new_field = make_set(player);
        if (!new_field) {
            return false;
        }

        old_fields[*old_fields_index_ptr] = g->board[current_x][current_y];
        (*old_fields_index_ptr)++;
        g->board[current_x][current_y] = new_field;
        unite(g->board[x][y], new_field);

        for (int i = 0; i < 4; ++i) {
            uint32_t x2 = adjacent[i].x;
            uint32_t y2 = adjacent[i].y;
            if (valid_coordinates(g, x2, y2) && get_player(g->board[x2][y2]) == player &&
                !connected(g->board[x][y], g->board[x2][y2])) {
                stack_node_t* new_last = put_last(stack_ptr, x2, y2);
                if (!new_last) {
                    remove_stack(stack_ptr);
                    free(adjacent);
                    return false;
                }
                stack_ptr = new_last;
            }
        }
        free(adjacent);
    }
    return true;
}

/** @brief Uruchamia algorytm dfs dla sąsiednich pól.
 * Przegląda tablicę pól @p adjacent i uruchami funkcję @ref dfs dla każdego z nich.
 * Liczy nowe obszary powstałe przy usunięciu pionka.
 * @param[in,out] g          – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] busy_player     – numer gracza na usuwanym polu, liczba dodatnia niewiększa
 *                             od wartości @p players z funkcji @ref gamma_new,
 * @param[in, out] adjacent  - maksymalnie czteroelementowa tablica par współrzędnych @p x i @p y
 * @param[in, out] old_fields - wskaźnik na pierwszy element tablicy wskaźników na pola,
 * @param[in, out] old_fields_index_ptr - wskaźnik na indeks pierwszego wolnego miejsca w tablicy
 * @p old_fields.
 * @return Liczba nowych obszarów w przypadku sukcesu, -2 jeśli wystąpiły problemy z pamięcią.
 */
static int dfs_on_adjacent(gamma_t* g, uint32_t busy_player, tuple* adjacent, find_union_node_t** old_fields,
                           uint64_t* old_fields_index_ptr) {
    // Usunięcie pionka może zmniejszyć liczbę obszarów o 1
    int new_areas = -1;

    for (int i = 0; i < 4; ++i) {
        uint32_t x2 = adjacent[i].x;
        uint32_t y2 = adjacent[i].y;
        if (valid_coordinates(g, x2, y2) && get_player(g->board[x2][y2]) == busy_player) {
            bool already_done_dfs = false;
            for (int j = 0; j < i; ++j) {
                uint32_t xj = adjacent[j].x;
                uint32_t yj = adjacent[j].y;
                already_done_dfs = already_done_dfs || (valid_coordinates(g, xj, yj) &&
                                                        connected(g->board[x2][y2], g->board[xj][yj]));
            }
            if (!already_done_dfs) {
                bool successful_dfs = dfs(g, x2, y2, old_fields, old_fields_index_ptr);
                // Jeśli pola po usunięciu przestają być połączone, to powstaje więcej obszarów
                new_areas++;
                if (!successful_dfs) {
                    free(adjacent);
                    for (uint64_t field = 0; field < *old_fields_index_ptr; ++field) {
                        free(old_fields[field]);
                    }
                    free(old_fields);
                    return -2;
                }
            }
        }
    }

    return new_areas;
}

/** @brief Przygotowanie do złotego ruchu.
 * Sprawdza poprwaność argumentów, alokuje pamięć na tablicę sąsiednich pól.
 * @param[in] g   – wskaźnik na strukturę przechowującą stan gry,
 * @param[in] player  – numer gracza, liczba dodatnia niewiększa od wartości
 *                      @p players z funkcji @ref gamma_new,
 * @param[in] x       – numer kolumny, liczba nieujemna mniejsza od wartości
 *                      @p width z funkcji @ref gamma_new,
 * @param[in] y       – numer wiersza, liczba nieujemna mniejsza od wartości
 *                      @p height z funkcji @ref gamma_new.
 * @return Tablica sąsiednich pól, @p NULL jeśli arugmenty są nieprawidłowe lub wystąpiły
 * problemy z alokacją pamięci.
 */
static tuple* golden_prep(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
    if (!g || !valid_player(g, player) || !valid_coordinates(g, x, y) || g->golden_moves[player] ||
        !g->board[x][y] || get_player(g->board[x][y]) == player) {
        return NULL;
    }
    tuple* adjacent = get_adjacent(g, x, y);
    if (!adjacent) {
        return NULL;
    }

    if (g->player_areas[player] == g->areas && !adjacent_with_player(g, player, adjacent)) {
        free(adjacent);
        return NULL;
    }
    return adjacent;
}

bool gamma_golden_move(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
    tuple* adjacent = golden_prep(g, player, x, y);
    if (!adjacent) {
        return false;
    }

    // Tablica na stare pola, które są połączone z usuwanym polem
    find_union_node_t** old_fields = calloc(2 * (uint64_t) g->height * (uint64_t) g->width, sizeof(find_union_node_t*));
    if (!old_fields) {
        free(adjacent);
        return false;
    }
    uint32_t busy_player = get_player(g->board[x][y]);

    old_fields[0] = g->board[x][y];
    uint64_t old_fields_index = 1;
    g->board[x][y] = NULL;

    int new_areas = dfs_on_adjacent(g, busy_player, adjacent, old_fields, &old_fields_index);
    if (new_areas == -2) {
        free(adjacent);
        return false;
    }

    // Usuwamy pionek, zwiększamy wolne pola o 1
    update_adjacent_free(g, adjacent, 1);

    int free_adjacent_fields = new_free_adjacent(g, busy_player, adjacent);
    if (free_adjacent_fields < 0) {
        free(adjacent);
        return false;
    }
    free(adjacent);
    for (uint64_t field = 0; field < old_fields_index; ++field) {
        free(old_fields[field]);
    }
    free(old_fields);

    g->free_adjacent_fields[busy_player] -= free_adjacent_fields;
    g->free_fields++;
    g->busy_fields[busy_player]--;
    g->player_areas[busy_player] += new_areas;

    if (g->player_areas[busy_player] > g->areas) {
        // Jeśli obszarów jest za dużo, to stawiamy stary pionek
        gamma_move(g, busy_player, x, y);
        return false;
    }

    g->golden_moves[player] = true;
    gamma_move(g, player, x, y);
    return true;
}

uint64_t gamma_busy_fields(gamma_t* g, uint32_t player) {
    if (!g || !valid_player(g, player)) {
        return 0;
    } else {
        return g->busy_fields[player];
    }
}

uint64_t gamma_free_fields(gamma_t* g, uint32_t player) {
    if (!g || !valid_player(g, player)) {
        return 0;
    }
    if (g->player_areas[player] == g->areas) {
        // Jeśli gracz zajmuje maksymalną liczbę obszarów, to może stawiać pionki
        // tylko na polach sąsiednich do swoich
        return g->free_adjacent_fields[player];
    }
    return g->free_fields;
}

bool golden_possible_on_field(gamma_t* g, uint32_t player, uint32_t x, uint32_t y) {
    if (g->golden_moves[player]) {
        return false;
    }
    uint32_t other_player = get_player(g->board[x][y]);
    bool other_player_used = g->golden_moves[other_player];

    if (gamma_golden_move(g, player, x, y)) {
        g->golden_moves[other_player] = false;
        gamma_golden_move(g, other_player, x, y);
        g->golden_moves[other_player] = other_player_used;
        g->golden_moves[player] = false;
        return true;
    } else {
        return false;
    }
}

bool gamma_golden_possible(gamma_t* g, uint32_t player) {
    if (!g || !valid_player(g, player) || g->golden_moves[player]) {
        return false;
    }

    if (g->player_areas[player] == g->areas) {
        for (uint32_t x = 0; x < g->width; ++x) {
            for (uint32_t y = 0; y < g->height; ++y) {
                if (golden_possible_on_field(g, player, x, y)) {
                    return true;
                }
            }
        }
    } else if (g->player_areas[player] < g->areas) {
        for (uint32_t other_player = 1; valid_player(g, other_player); ++other_player) {
            if (g->busy_fields[other_player] > 0 && player != other_player) {
                return true;
            }
        }
    }
    return false;
}

char* gamma_board(gamma_t* g) {
    // Numer aktualnego gracz równy 0 oznacza, że nie checmy podświetlać żadnego pola
    return board_with_highlight(g, 0, 0, 0);
}
