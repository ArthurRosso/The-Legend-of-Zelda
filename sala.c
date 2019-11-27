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

void gera_sala (SALA *sala)
{
    int i;
    time_t t;

    //srand((unsigned) time(&t));

    sala->link.pos.y = LINES-3;
    sala->link.pos.x = 0;
    sala->link.pos.dir = 1;

    desenha_jogador(&sala->link);

    for (i=0; i < NRO_INIS_MAX; i++)
    {
        sala->inis[i].vida=1;

        // TODO: testar se não nasce inimigos em cima de inimigo ou em cima do jogador
        sala->inis[i].pos.y=rand() % LINES-3;
        sala->inis[i].pos.x=rand() % COLS-3;

        sala->inis[i].cod = 0;

        if (i==0)
        {
            sala->inis[i].item=2;
        }
        sala->inis[i].item=1;

        //sala->inis[i].item=(rand() % 2);
        //sala->inis[i].cod=(rand() % 2);

        sala->inis[i].timer=0;

        desenha_inimigo(&sala->inis[i]);
    }
}

void move_jogador (SALA *sala)
{
    int ch;

    desenha_jogador(&sala->link);
    refresh();

    ch = getch();
    switch (ch)
    {
    case KEY_UP:
        if (sala->link.pos.y > 0)
        {
            sala->link.pos.y = sala->link.pos.y - 1;
            sala->link.pos.dir=0;
        }
        break;
    case KEY_RIGHT:
        if (sala->link.pos.x < COLS - 3)
        {
            sala->link.pos.x = sala->link.pos.x + 1;
            sala->link.pos.dir=1;
        }
        break;
    case KEY_LEFT:
        if (sala->link.pos.x > 0)
        {
            sala->link.pos.x = sala->link.pos.x - 1;
            sala->link.pos.dir=2;
        }
        break;
    case KEY_DOWN:
        if (sala->link.pos.y < LINES - 3)
        {
            sala->link.pos.y = sala->link.pos.y + 1;
            sala->link.pos.dir=3;
        }
        break;
    case SPACE:
        ataque_magico(sala);
        break;
    }

}

void ataque_magico (SALA *sala)
{

    int i, j;
    switch (sala->link.pos.dir)
    {
    case 0:
        for (i=0; i <= sala->link.pos.y; i++)
        {
            mvaddch(sala->link.pos.y-1-i, sala->link.pos.x+1, P_ATUD);
            refresh();
            for(j=0; j < NRO_INIS_MAX; j++)
            {
                if((sala->link.pos.x+1) == (sala->inis[j].pos.x+1))
                {
                    sala->inis[j].vida=0;
                }
            }
        }
        break;
    case 1:
        for (i=0; i<= COLS - sala->link.pos.x; i++)
        {
            mvaddch(sala->link.pos.y+1, sala->link.pos.x+3+i, P_ATRL);
            refresh();
            for(j=0; j < NRO_INIS_MAX; j++)
            {
                if( (sala->link.pos.y+1) == (sala->inis[j].pos.y+1) )
                {
                    sala->inis[j].vida=0;
                }
            }
        }
        break;
    case 2:
        for (i=0; i<=sala->link.pos.x; i++)
        {
            mvaddch(sala->link.pos.y+1, sala->link.pos.x-1-i, P_ATRL);
            refresh();
            for(j=0; j < NRO_INIS_MAX; j++)
            {
                if( (sala->link.pos.y+1) == (sala->inis[j].pos.y+1) )
                {
                    sala->inis[j].vida=0;
                }
            }
        }
        break;
    case 3:
        for (i=0; i<= (LINES - sala->link.pos.y); i++)
        {
            mvaddch(sala->link.pos.y+3+i, sala->link.pos.x+1, P_ATUD);
            refresh();
            for(j=0; j < NRO_INIS_MAX; j++)
            {
                if( (sala->link.pos.x+i) == (sala->inis[j].pos.x+i) )
                {
                    sala->inis[j].vida=0;
                }
            }
        }
        break;
    }
    refresh();
}

void updateInimigo(SALA *sala, INIMIGO *ini, float deltaTime)
{
    if (ini->vida==1){
        // Aumeta o timer
        ini->timer += deltaTime;
        desenha_inimigo(ini);

        // cada lance do timer o inimigo pode se mover
        if (ini->timer >= 1)
        {
            ini->timer = 0;

            move_inimigo(sala, ini);
        }
    }
}

void move_inimigo (SALA *sala, INIMIGO *ini)
{
    //if(ini->vida == 1)
    //{
        if(sala->link.pos.y != ini->pos.y)
        {
            if ((sala->link.pos.y) > (ini->pos.y))
            {
                ini->pos.y++;
            }
            else
            {
                ini->pos.y--;
            }
            desenha_inimigo(ini);
        }
        if((sala->link.pos.x!=ini->pos.x))
        {
            if((sala->link.pos.x)>(ini->pos.x))
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
