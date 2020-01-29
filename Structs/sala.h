#ifndef SALA_H
#define SALA_H

#define NRO_INIS_MAX 10

#include "inimigo.h"
#include "jogador.h"

typedef struct t_sala
{
    int numInis; // Dificuldade
    INIMIGO inis[NRO_INIS_MAX]; //com 10 inimigos da pra ganhar
    JOGADOR link;
} SALA;

void gera_sala (SALA *sala, int numInis);

void move_jogador (SALA *sala, int ch);
void ataque_magico (SALA *sala);

void move_inimigo (SALA *sala, INIMIGO *ini);
void updateInimigo(SALA *sala, INIMIGO *ini, float deltaTime);
void addPont(SALA *sala, int indice);

#endif
