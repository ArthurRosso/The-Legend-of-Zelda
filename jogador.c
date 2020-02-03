#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "Structs/jogador.h"

void desenha_jogador (JOGADOR *link)
{
    switch (link->pos.dir)
    {
    case 0:
        mvaddch(link->pos.y+3, link->pos.x,   EMPTY);
        mvaddch(link->pos.y+3, link->pos.x+1, EMPTY);
        mvaddch(link->pos.y+3, link->pos.x+2, EMPTY);
        mvaddch(link->pos.y+2, link->pos.x,   EMPTY);
        mvaddch(link->pos.y,   link->pos.x+1, P_RARM);
        mvaddch(link->pos.y+1, link->pos.x,   P_HEAD);
        mvaddch(link->pos.y+1, link->pos.x+1, P_TRO1);
        mvaddch(link->pos.y+1, link->pos.x+2, P_TRO2);
        mvaddch(link->pos.y+2, link->pos.x+2, P_LFOO);
        mvaddch(link->pos.y+2, link->pos.x+1, P_LARM);
        mvaddch(link->pos.y,   link->pos.x+2, P_RFOO);
        if (link->chave == 1){
            mvaddch(link->pos.y-1,   link->pos.x+2, '~');
        }
        break;
    case 1:
        mvaddch(link->pos.y,   link->pos.x-1, EMPTY);
        mvaddch(link->pos.y+1, link->pos.x-1, EMPTY);
        mvaddch(link->pos.y+2, link->pos.x-1, EMPTY);
        mvaddch(link->pos.y,   link->pos.x,   EMPTY);
        mvaddch(link->pos.y,   link->pos.x+1, P_HEAD);
        mvaddch(link->pos.y+1, link->pos.x,   P_LARM);
        mvaddch(link->pos.y+1, link->pos.x+1, P_TRO1);
        mvaddch(link->pos.y+1, link->pos.x+2, P_RARM);
        mvaddch(link->pos.y+2, link->pos.x,   P_LFOO);
        mvaddch(link->pos.y+2, link->pos.x+1, P_TRO2);
        mvaddch(link->pos.y+2, link->pos.x+2, P_RFOO);
        if (link->chave == 1){
            mvaddch(link->pos.y+1,   link->pos.x+4, '~');
        }
        break;
    case 2:
        mvaddch(link->pos.y,   link->pos.x+2, EMPTY);
        mvaddch(link->pos.y,   link->pos.x+3, EMPTY);
        mvaddch(link->pos.y+1, link->pos.x+3, EMPTY);
        mvaddch(link->pos.y+2, link->pos.x+3, EMPTY);
        mvaddch(link->pos.y,   link->pos.x+1, P_HEAD);
        mvaddch(link->pos.y+1, link->pos.x,   P_RARM);
        mvaddch(link->pos.y+1, link->pos.x+1, P_TRO1);
        mvaddch(link->pos.y+1, link->pos.x+2, P_LARM);
        mvaddch(link->pos.y+2, link->pos.x,   P_LFOO);
        mvaddch(link->pos.y+2, link->pos.x+1, P_TRO2);
        mvaddch(link->pos.y+2, link->pos.x+2, P_RFOO);
        if (link->chave == 1){
            mvaddch(link->pos.y+1,   link->pos.x-1, '~');
        }
        break;
    case 3:
        mvaddch(link->pos.y,   link->pos.x,   EMPTY);
        mvaddch(link->pos.y-1, link->pos.x+1, EMPTY);
        mvaddch(link->pos.y-1, link->pos.x+2, EMPTY);
        mvaddch(link->pos.y-1, link->pos.x+3, EMPTY);
        mvaddch(link->pos.y,   link->pos.x+1, P_LARM);
        mvaddch(link->pos.y+1, link->pos.x,   P_HEAD);
        mvaddch(link->pos.y+1, link->pos.x+1, P_TRO1);
        mvaddch(link->pos.y+1, link->pos.x+2, P_TRO2);
        mvaddch(link->pos.y+2, link->pos.x+2, P_LFOO);
        mvaddch(link->pos.y+2, link->pos.x+1, P_RARM);
        mvaddch(link->pos.y,   link->pos.x+2, P_RFOO);
        if (link->chave == 1){
            mvaddch(link->pos.y+3,   link->pos.x+2, '~');
        }
        break;
    }

    //attron(COLOR_PAIR(4));
    move(link->pos.y, link->pos.x);
    refresh();
}

