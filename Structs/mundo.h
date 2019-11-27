#ifndef MUNDO_H
#define MUNDO_H

#include "sala.h"
#include "jogador.h"

typedef struct t_mun
{
    SALA sala;
    JOGADOR link;
} MUNDO;

void gera_mundo (MUNDO *mundo);
void move_jogador (MUNDO *world);
void ataque_magico (MUNDO *world);

void move_inimigo (MUNDO *world, INIMIGO *ini);
void updateInimigo(MUNDO *world, INIMIGO *ini, float deltaTime);

#endif
