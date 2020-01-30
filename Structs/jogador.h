#ifndef JOGADOR_H
#define JOGADOR_H

#include "coordenadas.h"

#define P_HEAD '#'
#define P_LARM '@'
#define P_TRO1 '#'
#define P_RARM '$'
#define P_LFOO '#'
#define P_TRO2 '#'
#define P_RFOO '#'
#define P_ATUD '|'
#define P_ATRL '-'

#define GHINI 0
#define OKTOROK 1

#define ESC 27
#define SPACE 32
#define EMPTY ' '

typedef struct t_jog
{
    int vida;
    int nivel;
    COORDENADAS pos; // posicao
    int pont; // pontuacao atual
    int chave; //valor que determina troca de sala
    float timer;
    //int vel; // A velocidade do jogador cresce a cada mudança de sala.
} JOGADOR;

void desenha_jogador (JOGADOR *link);

#endif //JOGADOR_H
