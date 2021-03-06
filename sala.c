#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <poll.h> // poll(), struct pollfd e POLLIN
#include <time.h>

#include "Structs/sala.h"
#include "Structs/jogador.h"
#include "Structs/inimigo.h"

void gera_sala(SALA *sala, int numInis)
{
    clear();
    int i;
    time_t t;

    //srand((unsigned) time(&t));

    sala->link.pos.y = LINES - 3;
    sala->link.pos.x = 0;
    sala->link.pos.dir = 1;
    sala->link.timer = 0;

    sala->numInis = numInis;
    sala->link.nivel = numInis;

    if (numInis == 1)
    {
        sala->link.vida = 3;
        sala->link.pont = 0;
    }

    desenha_jogador(&sala->link);

    for (i = 0; i < sala->numInis; i++)
    {
        sala->inis[i].vida = 1;

        // TODO: testar se não nasce inimigos em cima de inimigo ou em cima do jogador
        sala->inis[i].pos.y = rand() % LINES - 3;
        sala->inis[i].pos.x = rand() % COLS - 3;

        sala->inis[i].cod = 0;
        //sala->inis[i].cod=(rand() % 2);

        if (i == 0)
        {
            sala->inis[i].item = 2;
        }
        else
        {
            sala->inis[i].item = 1;
            //sala->inis[i].item=(rand() % 2);
        }

        sala->inis[i].timer = 0;

        desenha_inimigo(&sala->inis[i]);
    }
    //draw_map();
}

int salva_sala(SALA *sala)
{
    clear();
    int resultado;
    FILE *arq;

    arq = fopen(FILE_NAME, "wb");

    if (arq == NULL)
    {
        resultado = -1;
    }
    else
    {
        resultado = fwrite(sala, sizeof(SALA), 1, arq);
    }

    fclose(arq);

    return resultado;
}

int carrega_sala(SALA *sala)
{
    clear();
    int resultado, i;
    FILE *arq;

    arq = fopen(FILE_NAME, "rb");

    if (arq == NULL)
    {
        resultado = -1;
    }
    else
    {
        resultado = fread(sala, sizeof(SALA), 1, arq);
    }

    fclose(arq);

    desenha_jogador(&sala->link);

    for (i = 0; i < sala->numInis; i++)
    {
        desenha_inimigo(&sala->inis[i]);
    }

    return resultado;
}

void move_jogador(SALA *sala, int ch)
{
    switch (ch)
    {
    case KEY_UP:
        if (sala->link.pos.y > 0)
        {
            sala->link.pos.y = sala->link.pos.y - 1;
            sala->link.pos.dir = 0;
        }
        break;
    case KEY_RIGHT:
        if (sala->link.pos.x < COLS - 3)
        {
            sala->link.pos.x = sala->link.pos.x + 1;
            sala->link.pos.dir = 1;
            if ((sala->link.chave == 1) && (sala->link.pos.x == COLS - 3) && (sala->link.nivel <= NRO_INIS_MAX))
            {
                //TODO: limpar a tela e criar
                sala->link.chave = 0;
                sala->link.pont += 5;
                //TODO: percorrer um for limpando os inimigos
                gera_sala(sala, sala->link.nivel + 1);
            } else if (sala->link.nivel > NRO_INIS_MAX){
                sala->link.vida = 0;
            }
        }
        break;
    case KEY_LEFT:
        if (sala->link.pos.x > 0)
        {
            sala->link.pos.x = sala->link.pos.x - 1;
            sala->link.pos.dir = 2;
        }
        break;
    case KEY_DOWN:
        if (sala->link.pos.y < LINES - 3)
        {
            sala->link.pos.y = sala->link.pos.y + 1;
            sala->link.pos.dir = 3;
        }
        break;
    case SPACE:
        ataque_magico(sala);
        break;
    }

    desenha_jogador(&sala->link);
    refresh();
}

void ataque_magico(SALA *sala)
{

    int i, j;
    switch (sala->link.pos.dir)
    {
    case 0:
        for (i = 0; i <= sala->link.pos.y; i++)
        {
            mvaddch(sala->link.pos.y - 1 - i, sala->link.pos.x + 1, P_ATUD);
            refresh();
            for (j = 0; j < sala->numInis; j++)
            {
                if ((sala->link.pos.x + 1) == (sala->inis[j].pos.x + 1))
                {
                    sala->inis[j].vida = 0;
                    //addPont(sala, j);
                }
            }
        }
        break;
    case 1:
        for (i = 0; i <= COLS - sala->link.pos.x; i++)
        {
            mvaddch(sala->link.pos.y + 1, sala->link.pos.x + 3 + i, P_ATRL);
            refresh();
            for (j = 0; j < sala->numInis; j++)
            {
                if ((sala->link.pos.y + 1) == (sala->inis[j].pos.y + 1))
                {
                    sala->inis[j].vida = 0;
                    //addPont(sala, j);
                }
            }
        }
        break;
    case 2:
        for (i = 0; i <= sala->link.pos.x; i++)
        {
            mvaddch(sala->link.pos.y + 1, sala->link.pos.x - 1 - i, P_ATRL);
            refresh();
            for (j = 0; j < sala->numInis; j++)
            {
                if ((sala->link.pos.y + 1) == (sala->inis[j].pos.y + 1))
                {
                    sala->inis[j].vida = 0;
                    //addPont(sala, j);
                }
            }
        }
        break;
    case 3:
        for (i = 0; i <= (LINES - sala->link.pos.y); i++)
        {
            mvaddch(sala->link.pos.y + 3 + i, sala->link.pos.x + 1, P_ATUD);
            refresh();
            for (j = 0; j < sala->numInis; j++)
            {
                if ((sala->link.pos.x + i) == (sala->inis[j].pos.x + i))
                {
                    sala->inis[j].vida = 0;
                    //addPont(sala, j);
                }
            }
        }
        break;
    }
    refresh();
}

void addPont(SALA *sala, int indice)
{
    if (sala->inis[indice].cod == GHINI)
    {
        sala->link.pont = sala->link.pont + 2;
    }
    else if (sala->inis[indice].cod == OKTOROK)
    {
        sala->link.pont++;
    }
}

void updateInimigo(SALA *sala, INIMIGO *ini, float deltaTime)
{
    if (ini->vida == 1)
    {
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
    else
    {
        desenha_lapide(ini);
        if ((sala->link.pos.y == ini->pos.y) && (sala->link.pos.x == ini->pos.x + 5))
        {
            if (ini->item == 1)
            {
                sala->link.vida++;
            }
            else if (ini->item == 2)
            {
                sala->link.chave = 1;
            }
        }
    }
}

void move_inimigo(SALA *sala, INIMIGO *ini)
{
    if (sala->link.pos.y != ini->pos.y)
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
    if ((sala->link.pos.x != ini->pos.x))
    {
        if ((sala->link.pos.x) > (ini->pos.x))
        {
            ini->pos.x++;
        }
        else
        {
            ini->pos.x--;
        }
        desenha_inimigo(ini);
    }
}

void draw_map(void)
{
    int y, x;

    /* draw the quest map */

    /* background */

    attron(COLOR_PAIR(GRASS_PAIR));
    for (y = 0; y < LINES; y++)
    {
        mvhline(y, 0, GRASS, COLS);
    }
    attroff(COLOR_PAIR(GRASS_PAIR));

    /* mountains, and mountain path */

    attron(COLOR_PAIR(MOUNTAIN_PAIR));
    for (x = COLS / 2; x < COLS * 3 / 4; x++)
    {
        mvvline(0, x, MOUNTAIN, LINES);
    }
    attroff(COLOR_PAIR(MOUNTAIN_PAIR));

    attron(COLOR_PAIR(GRASS_PAIR));
    mvhline(LINES / 4, 0, GRASS, COLS);
    attroff(COLOR_PAIR(GRASS_PAIR));

    /* lake */

    attron(COLOR_PAIR(WATER_PAIR));
    for (y = 1; y < LINES / 2; y++)
    {
        mvhline(y, 1, WATER, COLS / 3);
    }
    attroff(COLOR_PAIR(WATER_PAIR));
}