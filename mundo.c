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

void gera_mundo (MUNDO *mundo)
{
    mundo->link.pos.y = LINES-3;
    mundo->link.pos.x = 0;
    mundo->link.pos.dir = 1;

    desenha_jogador(&mundo->link);

    gera_sala(&mundo->sala);
}

void move_jogador (MUNDO *world)
{
    int ch;

    desenha_jogador(&world->link);
    refresh();

    ch = getch();
    switch (ch)
    {
    case KEY_UP:
        if (world->link.pos.y > 0)
        {
            world->link.pos.y = world->link.pos.y - 1;
            world->link.pos.dir=0;
        }
        break;
    case KEY_RIGHT:
        if (world->link.pos.x < COLS - 3)
        {
            world->link.pos.x = world->link.pos.x + 1;
            world->link.pos.dir=1;
        }
        break;
    case KEY_LEFT:
        if (world->link.pos.x > 0)
        {
            world->link.pos.x = world->link.pos.x - 1;
            world->link.pos.dir=2;
        }
        break;
    case KEY_DOWN:
        if (world->link.pos.y < LINES - 3)
        {
            world->link.pos.y = world->link.pos.y + 1;
            world->link.pos.dir=3;
        }
        break;
    case SPACE:
        ataque_magico(world);
        break;
    }

}

void ataque_magico (MUNDO *world)
{

    int i, j;
    switch (world->link.pos.dir)
    {
    case 0:
        for (i=0; i <= world->link.pos.y; i++)
        {
            mvaddch(world->link.pos.y-1-i, world->link.pos.x+1, P_ATUD);
            refresh();
            for(j=0; j < NRO_INIS; j++)
            {
                if((world->link.pos.x+1) == (world->sala.inis[j].pos.x+1))
                {
                    world->sala.inis[j].vida=0;
                }
            }
        }
        break;
    case 1:
        for (i=0; i<= COLS - world->link.pos.x; i++)
        {
            mvaddch(world->link.pos.y+1, world->link.pos.x+3+i, P_ATRL);
            refresh();
            for(j=0; j < NRO_INIS; j++)
            {
                if( (world->link.pos.y+1) == (world->sala.inis[j].pos.y+1) )
                {
                    world->sala.inis[j].vida=0;
                }
            }
        }
        break;
    case 2:
        for (i=0; i<=world->link.pos.x; i++)
        {
            mvaddch(world->link.pos.y+1, world->link.pos.x-1-i, P_ATRL);
            refresh();
            for(j=0; j < NRO_INIS; j++)
            {
                if( (world->link.pos.y+1) == (world->sala.inis[j].pos.y+1) )
                {
                    world->sala.inis[j].vida=0;
                }
            }
        }
        break;
    case 3:
        for (i=0; i<= (LINES - world->link.pos.y); i++)
        {
            mvaddch(world->link.pos.y+3+i, world->link.pos.x+1, P_ATUD);
            refresh();
            for(j=0; j < NRO_INIS; j++)
            {
                if( (world->link.pos.x+i) == (world->sala.inis[j].pos.x+i) )
                {
                    world->sala.inis[j].vida=0;
                }
            }
        }
        break;
    }
    refresh();
}

void updateInimigo(MUNDO *world, INIMIGO *ini, float deltaTime)
{
    if (ini->vida==1){
        // Aumeta o timer
        ini->timer += deltaTime;
        desenha_inimigo(ini);

        // cada lance do timer o inimigo pode se mover
        if (ini->timer >= 1)
        {
            ini->timer = 0;

            move_inimigo(world, ini);
        }
    }
}

void move_inimigo (MUNDO *world, INIMIGO *ini)
{
    //if(ini->vida == 1)
    //{
        if(world->link.pos.y != ini->pos.y)
        {
            if ((world->link.pos.y) > (ini->pos.y))
            {
                ini->pos.y++;
            }
            else
            {
                ini->pos.y--;
            }
            desenha_inimigo(ini);
        }
        if((world->link.pos.x!=ini->pos.x))
        {
            if((world->link.pos.x)>(ini->pos.x))
            {
                ini->pos.x++;
            }
            else
            {
                ini->pos.x--;
            }
            desenha_inimigo(ini);
        }
    //}
}
