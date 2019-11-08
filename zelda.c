#include <curses.h>
#include <stdlib.h>
#include<stdlib.h>
#include <string.h>

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

typedef struct pos
{
    int x;
    int y;
    int dir;
} COORDENADAS;

typedef struct jog
{
    int vida;
    COORDENADAS posicao;
    //char sprite[3][3]= {' ', '#', ' ', '@'};
    char sprite[TAM_SPRITE][TAM_SPRITE];
    char nome[TAM_NOME];
    int pontuacao;
} JOGADOR;

typedef struct ini
{
    int vida;
    COORDENADAS posicao;
    //char sprite[3][3];
    int codigo; //para diferenciar entre os inimigos
} INIMIGO;

void swap(JOGADOR *a, JOGADOR *b)
{
    JOGADOR temp = *a;
    *a = *b;
    *b = temp;
}

void desenha_jogador (JOGADOR link);
void ataque_magico (int y, int x, int dir);
void desenha_inimigo (int y, int x, int dir, int cod);
//void movimenta_jogador (JOGADOR link, int ch);
void ordena_pontuacao(JOGADOR jogadores[], int tamanho);
int le_arquivo_pontuacao(char nome_arquivo[],JOGADOR jogadores[],int tamanho);
int escreve_arquivo_pontuacao(char nome_arquivo[], JOGADOR jogadores[],int tamanho);

int main(void)
{
    JOGADOR link[2];

    strcpy(link[0].nome,"a");
    link[0].pontuacao = 123;
    int r = escreve_arquivo_pontuacao("wb.bin",link, 1);
    JOGADOR test[1];
    le_arquivo_pontuacao("wb.bin", test, 1);
    printf("%s: %d\n", test[0].nome,test[0].pontuacao);

    /*int i_y, i_x, i_dir, i_cod;
    int ch;

    initscr();
    keypad(stdscr, TRUE);
    cbreak();
    noecho();
    curs_set(0);

    link.posicao.y = LINES - 3;
    link.posicao.x = 0;
    link.posicao.dir=1;

    desenha_jogador(link);*/


    /*
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
            ataque_magico(link.posicao.y, link.posicao.x, link.posicao.dir);
            break;
        }

        desenha_jogador(link);

        //if (ch != ESC) {
        //    movimenta_jogador(link,ch);
        //} else {
        //TODO implementar funcao de salvar
        //}

    }
    while ((ch != ESC));*/

    endwin();

    exit(0);
}

void desenha_jogador (JOGADOR link)
{
    int y = link.posicao.y;
    int x = link.posicao.x;
    int dir = link.posicao.dir;
    switch (dir)
    {
    case 0:
        mvaddch(y+3, x, EMPTY);
        mvaddch(y+3, x+1, EMPTY);
        mvaddch(y+3, x+2, EMPTY);
        mvaddch(y+2, x, EMPTY);
        mvaddch(y, x+1, P_RARM);
        mvaddch(y+1, x, P_HEAD);
        mvaddch(y+1, x+1, P_TRO1);
        mvaddch(y+1, x+2, P_TRO2);
        mvaddch(y+2, x+2, P_LFOO);
        mvaddch(y+2, x+1, P_LARM);
        mvaddch(y, x+2, P_RFOO);
        break;
    case 1:
        mvaddch(y, x-1, EMPTY);
        mvaddch(y+1, x-1, EMPTY);
        mvaddch(y+2, x-1, EMPTY);
        mvaddch(y, x, EMPTY);
        mvaddch(y, x+1, P_HEAD);
        mvaddch(y+1, x, P_LARM);
        mvaddch(y+1, x+1, P_TRO1);
        mvaddch(y+1, x+2, P_RARM);
        mvaddch(y+2, x, P_LFOO);
        mvaddch(y+2, x+1, P_TRO2);
        mvaddch(y+2, x+2, P_RFOO);
        break;
    case 2:
        mvaddch(y, x+2, EMPTY);
        mvaddch(y, x+3, EMPTY);
        mvaddch(y+1, x+3, EMPTY);
        mvaddch(y+2, x+3, EMPTY);
        mvaddch(y, x+1, P_HEAD);
        mvaddch(y+1, x, P_RARM);
        mvaddch(y+1, x+1, P_TRO1);
        mvaddch(y+1, x+2, P_LARM);
        mvaddch(y+2, x, P_LFOO);
        mvaddch(y+2, x+1, P_TRO2);
        mvaddch(y+2, x+2, P_RFOO);
        break;
    case 3:
        mvaddch(y, x, EMPTY);
        mvaddch(y-1, x+1, EMPTY);
        mvaddch(y-1, x+2, EMPTY);
        mvaddch(y-1, x+3, EMPTY);
        mvaddch(y, x+1, P_LARM);
        mvaddch(y+1, x, P_HEAD);
        mvaddch(y+1, x+1, P_TRO1);
        mvaddch(y+1, x+2, P_TRO2);
        mvaddch(y+2, x+2, P_LFOO);
        mvaddch(y+2, x+1, P_RARM);
        mvaddch(y, x+2, P_RFOO);
        break;
    }

    move(y, x);
    refresh();
}


void ataque_magico (int y, int x, int dir)
{
    int i;
    switch (dir)
    {
    case 0:
        for (i=0; i<=y; i++)
        {
            mvaddch(y-1-i, x+1, P_ATUD);
        }
        break;
    case 1:
        for (i=0; i<=COLS-x; i++)
        {
            mvaddch(y+1, x+1+i, P_ATRL);
        }
        break;
    case 2:
        for (i=0; i<=x; i++)
        {
            mvaddch(y+1, x+1-i, P_ATRL);
        }
        break;
    case 3:
        for (i=0; i<=LINES-y; i++)
        {
            mvaddch(y-1+i, x+1, P_ATUD);
        }
        break;
    }
}

void desenha_inimigo (int y, int x, int dir, int cod)
{
    switch (cod)
    {
    case 1:
        mvaddch(y, x-1, EMPTY);
        mvaddch(y+1, x-1, EMPTY);
        mvaddch(y+2, x-1, EMPTY);
        mvaddch(y, x+2, G_RHAN);
        mvaddch(y, x, G_LHAN);
        mvaddch(y, x+1, G_HEAD);
        mvaddch(y+1, x, G_LARM);
        mvaddch(y+1, x+1, G_TRO1);
        mvaddch(y+1, x+2, G_RARM);
        mvaddch(y+2, x, G_LFOO);
        mvaddch(y+2, x+1, G_TRO2);
        mvaddch(y+2, x+2, G_RFOO);
        break;
    case 2:
        //TODO implementar o outro tipo de inimigo
        break;
    }

    move(y, x);
    refresh();
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
