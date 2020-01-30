#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "Structs/inimigo.h"

void desenha_inimigo (INIMIGO *ini)
{
    switch (ini->cod)
    {
    case GHINI:
        mvaddch(ini->pos.y+3, ini->pos.x-1, EMPTY);
        mvaddch(ini->pos.y+3, ini->pos.x,   EMPTY);
        mvaddch(ini->pos.y+3, ini->pos.x+1, EMPTY);
        mvaddch(ini->pos.y+3, ini->pos.x+2, EMPTY);
        mvaddch(ini->pos.y+3, ini->pos.x+3, EMPTY);
        mvaddch(ini->pos.y,   ini->pos.x+3, EMPTY);
        mvaddch(ini->pos.y+1, ini->pos.x+3, EMPTY);
        mvaddch(ini->pos.y+2, ini->pos.x+3, EMPTY);
        mvaddch(ini->pos.y,   ini->pos.x-1, EMPTY);
        mvaddch(ini->pos.y+1, ini->pos.x-1, EMPTY);
        mvaddch(ini->pos.y+2, ini->pos.x-1, EMPTY);
        mvaddch(ini->pos.y-1, ini->pos.x-1, EMPTY);
        mvaddch(ini->pos.y-1, ini->pos.x,   EMPTY);
        mvaddch(ini->pos.y-1, ini->pos.x+1, EMPTY);
        mvaddch(ini->pos.y-1, ini->pos.x+2, EMPTY);
        mvaddch(ini->pos.y-1, ini->pos.x+3, EMPTY);
        mvaddch(ini->pos.y,   ini->pos.x,   G_LHAN);
        mvaddch(ini->pos.y,   ini->pos.x+1, G_HEAD);
        mvaddch(ini->pos.y,   ini->pos.x+2, G_RHAN);
        mvaddch(ini->pos.y+1, ini->pos.x,   G_LARM);
        mvaddch(ini->pos.y+1, ini->pos.x+1, G_TRO1);
        mvaddch(ini->pos.y+1, ini->pos.x+2, G_RARM);
        mvaddch(ini->pos.y+2, ini->pos.x,   G_LFOO);
        mvaddch(ini->pos.y+2, ini->pos.x+1, G_TRO2);
        mvaddch(ini->pos.y+2, ini->pos.x+2, G_RFOO);
        break;
    case OKTOROK:
        switch (ini->pos.dir)
        {
        case 1:
            mvaddch(ini->pos.y,   ini->pos.x-1, EMPTY);
            mvaddch(ini->pos.y+1, ini->pos.x-1, EMPTY);
            mvaddch(ini->pos.y+2, ini->pos.x-1, EMPTY);
            mvaddch(ini->pos.y,   ini->pos.x,   O_LHAN);
            mvaddch(ini->pos.y,   ini->pos.x+1, O_HEAD);
            mvaddch(ini->pos.y,   ini->pos.x+2, O_RHAN);
            mvaddch(ini->pos.y+1, ini->pos.x,   O_LARM);
            mvaddch(ini->pos.y+1, ini->pos.x+1, O_TRO1);
            mvaddch(ini->pos.y+1, ini->pos.x+2, O_RARM);
            mvaddch(ini->pos.y+2, ini->pos.x,   O_LFOO);
            mvaddch(ini->pos.y+2, ini->pos.x+1, O_TRO2);
            mvaddch(ini->pos.y+2, ini->pos.x+2, O_RFOO);
            break;
        case 2:
            mvaddch(ini->pos.y,   ini->pos.x+3, EMPTY);
            mvaddch(ini->pos.y+1, ini->pos.x+3, EMPTY);
            mvaddch(ini->pos.y+2, ini->pos.x+3, EMPTY);
            mvaddch(ini->pos.y,   ini->pos.x,   O_LHAN);
            mvaddch(ini->pos.y,   ini->pos.x+1, O_HEAD);
            mvaddch(ini->pos.y,   ini->pos.x+2, O_RHAN);
            mvaddch(ini->pos.y+1, ini->pos.x,   O_RARM);
            mvaddch(ini->pos.y+1, ini->pos.x+1, O_TRO1);
            mvaddch(ini->pos.y+1, ini->pos.x+2, O_LARM);
            mvaddch(ini->pos.y+2, ini->pos.x,   O_LFOO);
            mvaddch(ini->pos.y+2, ini->pos.x+1, O_TRO2);
            mvaddch(ini->pos.y+2, ini->pos.x+2, O_RFOO);
            break;
        }

        break;
    }
    
    attron(COLOR_PAIR(4));
    move(ini->pos.y, ini->pos.x);
    refresh();
}

void desenha_lapide (INIMIGO *ini)
{
    char corn1 = 218 + '\0';
    char corn2 = 191 + '\0';
    char corn3 = 192 + '\0';
    char corn4 = 217 + '\0';
    char bonus;

    mvaddch(ini->pos.y,   ini->pos.x, EMPTY);
    mvaddch(ini->pos.y,   ini->pos.x+1, EMPTY);
    mvaddch(ini->pos.y,   ini->pos.x+2, EMPTY);
    mvaddch(ini->pos.y,   ini->pos.x+3, EMPTY);
    mvaddch(ini->pos.y+1, ini->pos.x,   EMPTY);
    mvaddch(ini->pos.y+1, ini->pos.x+1, EMPTY);
    mvaddch(ini->pos.y+1, ini->pos.x+1, EMPTY);
    mvaddch(ini->pos.y+1, ini->pos.x+2, EMPTY);
    mvaddch(ini->pos.y+1, ini->pos.x+3, EMPTY);
    mvaddch(ini->pos.y+2, ini->pos.x,   EMPTY);
    mvaddch(ini->pos.y+2, ini->pos.x+1, EMPTY);
    mvaddch(ini->pos.y+2, ini->pos.x+1, EMPTY);
    mvaddch(ini->pos.y+2, ini->pos.x+2, EMPTY);
    mvaddch(ini->pos.y+2, ini->pos.x+3, EMPTY);
    mvaddch(ini->pos.y, ini->pos.x, corn1);
    mvaddch(ini->pos.y, ini->pos.x+1, corn2);
    mvaddch(ini->pos.y-1, ini->pos.x, corn3);
    mvaddch(ini->pos.y-1, ini->pos.x+1, corn4);
    if (ini->item == 1){
        bonus = '!';
        mvaddch(ini->pos.y, ini->pos.x+5, bonus);
    } else if (ini->item == 2) {
        bonus = '~';
        mvaddch(ini->pos.y, ini->pos.x+5, bonus);
    }
    refresh();
}
