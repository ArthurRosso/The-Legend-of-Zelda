#ifndef SALA_H
#define SALA_H

#define NRO_INIS_MAX 10

#define GRASS     ' '
#define WATER     '~'
#define MOUNTAIN  '^'
#define PLAYER    '*'

#define GRASS_PAIR     1
#define EMPTY_PAIR     1
#define WATER_PAIR     2
#define MOUNTAIN_PAIR  3
#define PLAYER_PAIR    4

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

void draw_map(void);

#endif
