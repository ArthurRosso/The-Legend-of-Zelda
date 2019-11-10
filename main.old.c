#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ESC 27
#define SPACE 32
#define EMPTY ' '


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

#define GHINI 1
#define OKTOROK 2

#define TAM_NOME 15
#define TAM_SPRITE 3

typedef struct t_pos
{
    int x;
    int y;
    int dir; //direcao
} COORDENADAS;

typedef struct t_jog
{
    int vida;
    COORDENADAS posicao;
    //char sprite[3][3]= {' ', '#', ' ', '@'};
    char sprite[TAM_SPRITE][TAM_SPRITE];
    char nome[TAM_NOME];
    int pontuacao;
} JOGADOR;

typedef struct t_ini
{
    int vida;
    COORDENADAS posicao;
    //char sprite[3][3];
    int cod; // codigo para diferenciar entre os inimigos
} INIMIGO;

void swap(JOGADOR *a, JOGADOR *b)
{
    JOGADOR temp = *a;
    *a = *b;
    *b = temp;
}

void desenha_jogador (JOGADOR link);
void ataque_magico (JOGADOR link);
void desenha_inimigo (INIMIGO ini);
//void move_jogador (JOGADOR link, int ch);
void move_inimigo (JOGADOR link, INIMIGO ini);
int detector_colisao (JOGADOR link, INIMIGO ini);
void ordena_pontuacao(JOGADOR jogadores[], int tamanho);
int le_arquivo_pontuacao(char nome_arquivo[],JOGADOR jogadores[],int tamanho);
int escreve_arquivo_pontuacao(char nome_arquivo[], JOGADOR jogadores[],int tamanho);

int main(void)
{
    JOGADOR link;
    INIMIGO ini;
    int ch;

    initscr();
    keypad(stdscr, TRUE);
    cbreak();
    noecho();
    curs_set(0);

    link.posicao.y = LINES - 3;
    link.posicao.x = 0;
    link.posicao.dir = 1;

    ini.posicao.y = 0;
    ini.posicao.x = 0;
    ini.posicao.dir = 1;
    ini.cod = GHINI;

    desenha_jogador(link);
    desenha_inimigo(ini);
    move_inimigo(link, ini);

    do
    {
        ch = getch();

        switch (ch)
        {
        case KEY_UP:
        case 'w':
        case 'W':
            if (link.posicao.y > 0)
            {
                link.posicao.y = link.posicao.y - 1;
                link.posicao.dir=0;
            }
            break;
        case KEY_RIGHT:
        case 'd':
        case 'D':
            if (link.posicao.x < COLS - 3)
            {
                link.posicao.x = link.posicao.x + 1;
                link.posicao.dir=1;
            }
            break;
        case KEY_LEFT:
        case 'a':
        case 'A':
            if (link.posicao.x > 0)
            {
                link.posicao.x = link.posicao.x - 1;
                link.posicao.dir=2;
            }
            break;
        case KEY_DOWN:
        case 's':
        case 'S':
            if (link.posicao.y < LINES - 3)
            {
                link.posicao.y = link.posicao.y + 1;
                link.posicao.dir=3;
            }
            break;
        case SPACE:
            ataque_magico(link);
            break;
        }

        desenha_jogador(link);


        /* if (ch != ESC) {
            movimenta_jogador(link,ch);
        } else {
        TODO implementar funcao de salvar
          strcpy(link[0].nome,"Nome");
          link[0].pontuacao = 123;
          int r = escreve_arquivo_pontuacao("pontuacao.bin", link, 1);
          le_arquivo_pontuacao("pontuacao.bin", link, 1);
          printf("%s: %d\n", link[0].nome, link[0].pontuacao);
        }
        */

    }
    while ((ch != ESC));



    endwin();

    exit(0);
}

void desenha_jogador (JOGADOR link)
{
    switch (link.posicao.dir)
    {
    case 0:
        mvaddch(link.posicao.y+3, link.posicao.x,   EMPTY);
        mvaddch(link.posicao.y+3, link.posicao.x+1, EMPTY);
        mvaddch(link.posicao.y+3, link.posicao.x+2, EMPTY);
        mvaddch(link.posicao.y+2, link.posicao.x,   EMPTY);
        mvaddch(link.posicao.y,   link.posicao.x+1, P_RARM);
        mvaddch(link.posicao.y+1, link.posicao.x,   P_HEAD);
        mvaddch(link.posicao.y+1, link.posicao.x+1, P_TRO1);
        mvaddch(link.posicao.y+1, link.posicao.x+2, P_TRO2);
        mvaddch(link.posicao.y+2, link.posicao.x+2, P_LFOO);
        mvaddch(link.posicao.y+2, link.posicao.x+1, P_LARM);
        mvaddch(link.posicao.y,   link.posicao.x+2, P_RFOO);
        break;
    case 1:
        mvaddch(link.posicao.y,   link.posicao.x-1, EMPTY);
        mvaddch(link.posicao.y+1, link.posicao.x-1, EMPTY);
        mvaddch(link.posicao.y+2, link.posicao.x-1, EMPTY);
        mvaddch(link.posicao.y,   link.posicao.x,   EMPTY);
        mvaddch(link.posicao.y,   link.posicao.x+1, P_HEAD);
        mvaddch(link.posicao.y+1, link.posicao.x,   P_LARM);
        mvaddch(link.posicao.y+1, link.posicao.x+1, P_TRO1);
        mvaddch(link.posicao.y+1, link.posicao.x+2, P_RARM);
        mvaddch(link.posicao.y+2, link.posicao.x,   P_LFOO);
        mvaddch(link.posicao.y+2, link.posicao.x+1, P_TRO2);
        mvaddch(link.posicao.y+2, link.posicao.x+2, P_RFOO);
        break;
    case 2:
        mvaddch(link.posicao.y,   link.posicao.x+2, EMPTY);
        mvaddch(link.posicao.y,   link.posicao.x+3, EMPTY);
        mvaddch(link.posicao.y+1, link.posicao.x+3, EMPTY);
        mvaddch(link.posicao.y+2, link.posicao.x+3, EMPTY);
        mvaddch(link.posicao.y,   link.posicao.x+1, P_HEAD);
        mvaddch(link.posicao.y+1, link.posicao.x,   P_RARM);
        mvaddch(link.posicao.y+1, link.posicao.x+1, P_TRO1);
        mvaddch(link.posicao.y+1, link.posicao.x+2, P_LARM);
        mvaddch(link.posicao.y+2, link.posicao.x,   P_LFOO);
        mvaddch(link.posicao.y+2, link.posicao.x+1, P_TRO2);
        mvaddch(link.posicao.y+2, link.posicao.x+2, P_RFOO);
        break;
    case 3:
        mvaddch(link.posicao.y,   link.posicao.x,   EMPTY);
        mvaddch(link.posicao.y-1, link.posicao.x+1, EMPTY);
        mvaddch(link.posicao.y-1, link.posicao.x+2, EMPTY);
        mvaddch(link.posicao.y-1, link.posicao.x+3, EMPTY);
        mvaddch(link.posicao.y,   link.posicao.x+1, P_LARM);
        mvaddch(link.posicao.y+1, link.posicao.x,   P_HEAD);
        mvaddch(link.posicao.y+1, link.posicao.x+1, P_TRO1);
        mvaddch(link.posicao.y+1, link.posicao.x+2, P_TRO2);
        mvaddch(link.posicao.y+2, link.posicao.x+2, P_LFOO);
        mvaddch(link.posicao.y+2, link.posicao.x+1, P_RARM);
        mvaddch(link.posicao.y,   link.posicao.x+2, P_RFOO);
        break;
    }

    move(link.posicao.y, link.posicao.x);
    refresh();
}


void ataque_magico (JOGADOR link)
{
    int i;
    switch (link.posicao.dir)
    {
    case 0:
        for (i=0; i<=link.posicao.y; i++)
        {
            mvaddch(link.posicao.y-1-i, link.posicao.x+1, P_ATUD);
            usleep(1000);
        }
        break;
    case 1:
        for (i=0; i<=COLS-link.posicao.x; i++)
        {
            mvaddch(link.posicao.y+1, link.posicao.x+1+i, P_ATRL);
            usleep(1000);
        }
        break;
    case 2:
        for (i=0; i<=link.posicao.x; i++)
        {
            mvaddch(link.posicao.y+1, link.posicao.x+1-i, P_ATRL);
            usleep(1000);
        }
        break;
    case 3:
        for (i=0; i<=LINES-link.posicao.y; i++)
        {
            mvaddch(link.posicao.y-1+i, link.posicao.x+1, P_ATUD);
            usleep(1000);
        }
        break;
    }
    refresh();
}

void desenha_inimigo (INIMIGO ini)
{
    switch (ini.cod)
    {
    case GHINI:
        mvaddch(ini.posicao.y+3, ini.posicao.x,   EMPTY);
        mvaddch(ini.posicao.y+3, ini.posicao.x+1, EMPTY);
        mvaddch(ini.posicao.y+3, ini.posicao.x+2, EMPTY);
        mvaddch(ini.posicao.y,   ini.posicao.x+3, EMPTY);
        mvaddch(ini.posicao.y+1, ini.posicao.x+3, EMPTY);
        mvaddch(ini.posicao.y+2, ini.posicao.x+3, EMPTY);
        mvaddch(ini.posicao.y,   ini.posicao.x-1, EMPTY);
        mvaddch(ini.posicao.y+1, ini.posicao.x-1, EMPTY);
        mvaddch(ini.posicao.y+2, ini.posicao.x-1, EMPTY);
        mvaddch(ini.posicao.y-1, ini.posicao.x,   EMPTY);
        mvaddch(ini.posicao.y-1, ini.posicao.x+1, EMPTY);
        mvaddch(ini.posicao.y-1, ini.posicao.x+2, EMPTY);
        mvaddch(ini.posicao.y,   ini.posicao.x,   G_LHAN);
        mvaddch(ini.posicao.y,   ini.posicao.x+1, G_HEAD);
        mvaddch(ini.posicao.y,   ini.posicao.x+2, G_RHAN);
        mvaddch(ini.posicao.y+1, ini.posicao.x,   G_LARM);
        mvaddch(ini.posicao.y+1, ini.posicao.x+1, G_TRO1);
        mvaddch(ini.posicao.y+1, ini.posicao.x+2, G_RARM);
        mvaddch(ini.posicao.y+2, ini.posicao.x,   G_LFOO);
        mvaddch(ini.posicao.y+2, ini.posicao.x+1, G_TRO2);
        mvaddch(ini.posicao.y+2, ini.posicao.x+2, G_RFOO);
        break;
    case OKTOROK:
        switch (ini.posicao.dir)
        {
        case 1:
            mvaddch(ini.posicao.y,   ini.posicao.x-1, EMPTY);
            mvaddch(ini.posicao.y+1, ini.posicao.x-1, EMPTY);
            mvaddch(ini.posicao.y+2, ini.posicao.x-1, EMPTY);
            mvaddch(ini.posicao.y,   ini.posicao.x,   O_LHAN);
            mvaddch(ini.posicao.y,   ini.posicao.x+1, O_HEAD);
            mvaddch(ini.posicao.y,   ini.posicao.x+2, O_RHAN);
            mvaddch(ini.posicao.y+1, ini.posicao.x,   O_LARM);
            mvaddch(ini.posicao.y+1, ini.posicao.x+1, O_TRO1);
            mvaddch(ini.posicao.y+1, ini.posicao.x+2, O_RARM);
            mvaddch(ini.posicao.y+2, ini.posicao.x,   O_LFOO);
            mvaddch(ini.posicao.y+2, ini.posicao.x+1, O_TRO2);
            mvaddch(ini.posicao.y+2, ini.posicao.x+2, O_RFOO);
            break;
        case 2:
            mvaddch(ini.posicao.y,   ini.posicao.x+3, EMPTY);
            mvaddch(ini.posicao.y+1, ini.posicao.x+3, EMPTY);
            mvaddch(ini.posicao.y+2, ini.posicao.x+3, EMPTY);
            mvaddch(ini.posicao.y,   ini.posicao.x,   O_LHAN);
            mvaddch(ini.posicao.y,   ini.posicao.x+1, O_HEAD);
            mvaddch(ini.posicao.y,   ini.posicao.x+2, O_RHAN);
            mvaddch(ini.posicao.y+1, ini.posicao.x,   O_RARM);
            mvaddch(ini.posicao.y+1, ini.posicao.x+1, O_TRO1);
            mvaddch(ini.posicao.y+1, ini.posicao.x+2, O_LARM);
            mvaddch(ini.posicao.y+2, ini.posicao.x,   O_LFOO);
            mvaddch(ini.posicao.y+2, ini.posicao.x+1, O_TRO2);
            mvaddch(ini.posicao.y+2, ini.posicao.x+2, O_RFOO);
            break;
        }

        break;
    }

    move(ini.posicao.y, ini.posicao.x);
    refresh();
}

void move_inimigo (JOGADOR link, INIMIGO ini){
  while(detector_colisao(link, ini) != 1){
    if (link.posicao.y>ini.posicao.y){
      ini.posicao.y--;
    } else {
      ini.posicao.y++;
    }

    if(link.posicao.x>ini.posicao.x){
      ini.posicao.x--;
    } else {
      ini.posicao.x++;
    }
    desenha_inimigo(ini);
  }
}

int detector_colisao (JOGADOR link, INIMIGO ini){
  int colidiu;
  if((link.posicao.x==ini.posicao.x) && (link.posicao.y==ini.posicao.y)){
    colidiu = 1;
  } else {
    colidiu = 0;
  }
  return colidiu;
}

void ordena_pontuacao(JOGADOR jogadores[], int tamanho)
{
    for (int i=0; i<tamanho; i++)
    {
        if (jogadores[i].pontuacao > jogadores[i+1].pontuacao)
        {
            swap(&jogadores[i], &jogadores[i+1]);
        }
    }
    ordena_pontuacao(jogadores, tamanho-1);
}

int le_arquivo_pontuacao(char nome_arquivo[],JOGADOR jogadores[],int tamanho)
{
    FILE *arquivo;

    arquivo=fopen(nome_arquivo,"rb");

    if(arquivo==NULL)
    {
        tamanho=-1;
    }
    else
    {
        if( fread(jogadores,sizeof(JOGADOR),tamanho,arquivo) !=tamanho)
        {
            fclose(arquivo);
            return -1;
        }
        fclose(arquivo);
    }
    return tamanho;
}

int escreve_arquivo_pontuacao(char nome_arquivo[], JOGADOR jogadores[],int tamanho)
{
    FILE *arquivo;
    int resultado;

    arquivo=fopen(nome_arquivo, "wb");

    if(arquivo==NULL)
    {
        resultado= -1;
    }
    else
    {
        resultado=fwrite(jogadores,sizeof(JOGADOR),tamanho,arquivo);
    }
    return resultado;
}
