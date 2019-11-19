#ifndef SALA_H
#define SALA_H

#define NRO_INIS 10

#include "inimigo.h"

typedef struct t_sala
{
    int dif; // Dificuldade
    INIMIGO inis[NRO_INIS]; //inimigos
} SALA;

void gera_sala (SALA *sala);

#endif
