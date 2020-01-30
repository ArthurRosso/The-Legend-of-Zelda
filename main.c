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

#define timeIni 1000000
#define timeLink 100

int update (SALA *sala, float deltaTimeIni, float deltaTimeLink);

int main()
{
    initscr();
    setvbuf(stdout, NULL, _IOLBF, 0);
    keypad(stdscr, TRUE);
    cbreak();
    noecho();
    curs_set(0);
    int sair;

    SALA s;
    gera_sala(&s, 1);

    while (sair != ESC)
    {
        sair = update(&s, timeIni, timeLink);
        //usleep(FREQUENCY);
    }

    endwin();

    return 0;
}
