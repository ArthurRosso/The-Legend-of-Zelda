#ifndef INIMIGO_H
#define INIMIGO_H

#include "coordenadas.h"

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
#define EMPTY ' '

typedef struct t_ini
{
    int vida;
    COORDENADAS pos;
    int cod; // codigo para diferenciar entre os inimigos
    int item; // 0==nada, 1==1vida, 2==chave
    int timer;
} INIMIGO;

void desenha_inimigo (INIMIGO *ini);
void desenha_lapide (INIMIGO *ini);

#endif //INIMIGO_H
