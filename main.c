#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>    // poll(), struct pollfd e POLLIN
#include <time.h>

#include "Structs/sala.h"
#include "Structs/jogador.h"
#include "Structs/inimigo.h"

int update (SALA *sala);

int main()
{
    initscr();
    setvbuf(stdout, NULL, _IOLBF, 0);
    keypad(stdscr, TRUE);
    cbreak();
    noecho();
    curs_set(0);
    start_color();

    init_pair(GRASS_PAIR, COLOR_BLACK, COLOR_GREEN);
    init_pair(WATER_PAIR, COLOR_CYAN, COLOR_BLUE);
    init_pair(MOUNTAIN_PAIR, COLOR_BLACK, COLOR_WHITE);
    init_pair(PLAYER_PAIR, COLOR_BLACK, COLOR_GREEN);

    int sair;

    SALA s;
    gera_sala(&s, 1);

    sair = update(&s);

    endwin();

    return 0;
}
