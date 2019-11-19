#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>    // poll(), struct pollfd e POLLIN
#include <time.h>

#include "mundo.h"
#include "sala.h"
#include "jogador.h"
#include "inimigo.h"

#define FREQUENCY 1000

bool kbhit();
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

    while (1) {
      update(&m, FREQUENCY/1000000.0f);
      usleep(FREQUENCY);
    }

    endwin();

    return 0;
}

bool kbhit()
{
    struct pollfd pollstdin= {STDIN_FILENO, POLLIN, 0};
    return poll(&pollstdin, 1, 0)==1;
}
