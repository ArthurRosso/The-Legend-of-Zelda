#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>    // poll(), struct pollfd e POLLIN
#include <time.h>

#include "Structs/mundo.h"
#include "Structs/sala.h"
#include "Structs/jogador.h"
#include "Structs/inimigo.h"

#define FREQUENCY 1000

void update (MUNDO *world, float deltaTime);

int main()
{
    initscr();
    setvbuf(stdout, NULL, _IOLBF, 0);
    keypad(stdscr, TRUE);
    cbreak();
    noecho();
    curs_set(0);

    MUNDO m;
    gera_mundo(&m);

    while (1)
    {
        update(&m, FREQUENCY/100);
        usleep(FREQUENCY);
    }

    endwin();

    return 0;
}
