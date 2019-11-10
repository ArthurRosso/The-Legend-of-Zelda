#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>    // poll(), struct pollfd e POLLIN
#include <time.h>

#define ESC 27
#define SPACE 32
#define EMPTY ' '
#define NRO_SALAS 10

#define P_HEAD '#'
#define P_LARM '@'
#define P_TRO1 '#'
#define P_RARM '$'
#define P_LFOO '#'
#define P_TRO2 '#'
#define P_RFOO '#'
#define P_ATUD '|'
#define P_ATRL '-'

#define G_LHAN '*'
#define G_HEAD '0'
#define G_RHAN '*'
#define G_LARM '\\'
#define G_TRO1 'U'
#define G_RARM '/'
#define G_LFOO '\\'
#define G_TRO2 '~'
#define G_RFOO '/'

#define O_LHAN '/'
#define O_HEAD '~'
#define O_RHAN '\\'
#define O_LARM '|'
#define O_TRO1 '0'
#define O_RARM '='
#define O_LFOO '\\'
#define O_TRO2 '~'
#define O_RFOO '/'

#define GHINI 0
#define OKTOROK 1

typedef struct t_pos
{
    int x;
    int y;
    int dir; //direcao
} COORDENADAS;

typedef struct t_jog
{
    int vida;
    COORDENADAS pos; // posicao
} JOGADOR;

typedef struct t_ini
{
    int vida;
    COORDENADAS pos;
    int cod; // codigo para diferenciar entre os inimigos
    int item; // 0==nada, 1==1vida, 2==chave
} INIMIGO;

typedef struct t_sala
{
    int dif; // Dificuldade
    INIMIGO inis[NRO_SALAS]; //inimigos
    JOGADOR *link;
} SALA;


bool kbhit();
void desenha_jogador (JOGADOR *link);
void ataque_magico (JOGADOR *link, INIMIGO *ini);
void desenha_inimigo (INIMIGO *ini);
void move_inimigo (JOGADOR *link, INIMIGO *ini);
int detector_colisao (JOGADOR *link, INIMIGO *ini);
void gera_sala (SALA *sala);

int main(void)
{
    initscr();
    setvbuf(stdout, NULL, _IOLBF, 0);
    keypad(stdscr, TRUE);
    cbreak();
    noecho();
    curs_set(0);

    JOGADOR link;
    INIMIGO ini;
    int ch;

    link.pos.y = LINES-3;
    link.pos.x = 0;
    link.pos.dir = 1;

    ini.pos.y = 0;
    ini.pos.x = 0;
    ini.pos.dir = 1;
    ini.cod = GHINI;
    ini.vida = 1;

    desenha_jogador(&link);
    desenha_inimigo(&ini);

    do
    {

        if(!kbhit())
        {
            move_inimigo(&link, &ini);
        }
        else
        {
            ch = getch();
            switch (ch)
            {
            case KEY_UP:
                if (link.pos.y > 0)
                {
                    link.pos.y = link.pos.y - 1;
                    link.pos.dir=0;
                }
                break;
            case KEY_RIGHT:
                if (link.pos.x < COLS - 3)
                {
                    link.pos.x = link.pos.x + 1;
                    link.pos.dir=1;
                }
                break;
            case KEY_LEFT:
                if (link.pos.x > 0)
                {
                    link.pos.x = link.pos.x - 1;
                    link.pos.dir=2;
                }
                break;
            case KEY_DOWN:
                if (link.pos.y < LINES - 3)
                {
                    link.pos.y = link.pos.y + 1;
                    link.pos.dir=3;
                }
                break;
            case SPACE:
                ataque_magico(&link, &ini);
                break;
            }

            desenha_jogador(&link);
        }

    }
    while ((ch != ESC));

    endwin();

    return 0;
}

bool kbhit()
{
    struct pollfd pollstdin= {STDIN_FILENO, POLLIN, 0};
    return poll(&pollstdin, 1, 0)==1;
}

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
        break;
    }

    move(link->pos.y, link->pos.x);
    refresh();
}


void ataque_magico (JOGADOR *link, INIMIGO *ini)
{
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
}

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
            /*
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
              */
            break;
        }

        break;
    }

    move(ini->pos.y, ini->pos.x);
    refresh();
}

void move_inimigo (JOGADOR *link, INIMIGO *ini)
{
    if(ini->vida == 1)
    {
        if((link->pos.y!=ini->pos.y))
        {
            if ((link->pos.y) > (ini->pos.y))
            {
                ini->pos.y++;
            }
            else
            {
                ini->pos.y--;
            }
            desenha_inimigo(ini);
            refresh();
            usleep(200000);
        }
        if((link->pos.x!=ini->pos.x))
        {
            if((link->pos.x)>(ini->pos.x))
            {
                ini->pos.x++;
            }
            else
            {
                ini->pos.x--;
            }
            desenha_inimigo(ini);
            refresh();
            usleep(200000);
        }
    }
}

void gera_sala (SALA *sala){
  int i;
  time_t t;

  srand((unsigned) time(&t));

  for (i=0; i<=sala->dif; i++){
    sala->inis[i].vida=1;
    sala->inis[i].pos.y=rand() % LINES-3;
    if (sala->inis[i].pos.y==sala->link->pos.y){
      if(LINES-8<=0){
        sala->inis[i].pos.y+=8;
      } else {
        sala->inis[i].pos.y-=8;
      }
    }
    sala->inis[i].pos.x=rand() % COLS-3;
    if (sala->inis[i].pos.x==sala->link->pos.x){
      if(COLS-8<=0){
        sala->inis[i].pos.x+=8;
      } else {
        sala->inis[i].pos.x-=8;
      }
    }
    if (i==0){
        sala->inis[i].item=2;
    }
    sala->inis[i].item=(rand() % 2);
    sala->inis[i].cod=(rand() % 2);
  }
}
