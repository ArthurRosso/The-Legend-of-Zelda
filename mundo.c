#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>    // poll(), struct pollfd e POLLIN
#include <time.h>

#include "jogador.h"
#include "inimigo.h"
#include "sala.h"
#include "mundo.h"

void gera_mundo (MUNDO *mundo){
    gera_sala(&mundo->sala);
}

void move_jogador (MUNDO *world){

//   int ch;

//   link->pos.y = LINES-3;
//   link->pos.x = 0;
//   link->pos.dir = 1;

//   desenha_jogador(&link);

//   do
//   {
//           ch = getch();
//           switch (ch)
//           {
//           case KEY_UP:
//               if (link->pos.y > 0)
//               {
//                   link->pos.y = link->pos.y - 1;
//                   link->pos.dir=0;
//               }
//               break;
//           case KEY_RIGHT:
//               if (link->pos.x < COLS - 3)
//               {
//                   link->pos.x = link->pos.x + 1;
//                   link->pos.dir=1;
//               }
//               break;
//           case KEY_LEFT:
//               if (link->pos.x > 0)
//               {
//                   link->pos.x = link->pos.x - 1;
//                   link->pos.dir=2;
//               }
//               break;
//           case KEY_DOWN:
//               if (link->pos.y < LINES - 3)
//               {
//                   link->pos.y = link->pos.y + 1;
//                   link->pos.dir=3;
//               }
//               break;
//           case SPACE:
//               ataque_magico(&link, world);
//               break;
//           }

//           desenha_jogador(&link);

//   }while (ch != ESC);

}

void ataque_magico (MUNDO *world)
{
    /*
    int i;
    switch (link->pos.dir)
    {
    case 0:
        for (i=0; i<=link->pos.y; i++)
        {
            mvaddch(link->pos.y-1-i, link->pos.x+1, P_ATUD);
            refresh();
            if( ((link->pos.y-i) == (ini->pos.y-i)) && ((link->pos.x+1) == (link->pos.x+1)))
            {
                ini->vida=0;
            }
            usleep(5000);
        }
        break;
    case 1:
        for (i=0; i<=COLS-link->pos.x; i++)
        {
            mvaddch(link->pos.y+1, link->pos.x+3+i, P_ATRL);
            refresh();
            if( ((link->pos.y+1) == (ini->pos.y+1)) && ((link->pos.x+i) == (link->pos.x+i)))
            {
                ini->vida=0;
            }
            usleep(5000);
        }
        break;
    case 2:
        for (i=0; i<=link->pos.x; i++)
        {
            mvaddch(link->pos.y+1, link->pos.x-1-i, P_ATRL);
            refresh();
            if( ((link->pos.y+1) == (ini->pos.y+1)) && ((link->pos.x-i) == (link->pos.x-i)))
            {
                ini->vida=0;
            }
            usleep(5000);
        }
        break;
    case 3:
        for (i=0; i<=LINES-link->pos.y; i++)
        {
            mvaddch(link->pos.y+3+i, link->pos.x+1, P_ATUD);
            refresh();
            if( ((link->pos.y+i) == (ini->pos.y+i)) && ((link->pos.x+1) == (link->pos.x+1)))
            {
                ini->vida=0;
            }
            usleep(5000);
        }
        break;
    }
    refresh();
    */
}

void updateInimigo(MUNDO *world, INIMIGO *ini, float deltaTime) {
    // Aumeta o timer
    ini->timer += deltaTime;

    if (ini->timer >= 1) {
        ini->timer = 0;

        move_inimigo(&world->link, &ini);
    }
}

void move_inimigo (MUNDO *world, INIMIGO *ini)
{
    // if(ini->vida == 1)
    // {
    //     if((link->pos.y!=ini->pos.y))
    //     {
    //         if ((link->pos.y) > (ini->pos.y))
    //         {
    //             ini->pos.y++;
    //         }
    //         else
    //         {
    //             ini->pos.y--;
    //         }
    //         desenha_inimigo(ini);
    //         refresh();
    //         usleep(200000);
    //     }
    //     if((link->pos.x!=ini->pos.x))
    //     {
    //         if((link->pos.x)>(ini->pos.x))
    //         {
    //             ini->pos.x++;
    //         }
    //         else
    //         {
    //             ini->pos.x--;
    //         }
    //         desenha_inimigo(ini);
    //         refresh();
    //         usleep(200000);
    //     }
    // }
}
