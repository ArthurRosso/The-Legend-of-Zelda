#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>    // poll(), struct pollfd e POLLIN
#include <time.h>

#include "Structs/mundo.h"
#include "Structs/sala.h"
#include "Structs/jogador.h"
#include "Structs/inimigo.h"

void gera_sala (SALA *sala)
{
    int i;
    time_t t;

    //srand((unsigned) time(&t));

    for (i=0; i < NRO_INIS; i++)
    {
        sala->inis[i].vida=1;

        // TODO: testar se não nasce inimigos em cima de inimigo ou em cima do jogador
        sala->inis[i].pos.y=rand() % LINES-3;
        sala->inis[i].pos.x=rand() % COLS-3;

        sala->inis[i].cod = 0;

        if (i==0)
        {
            sala->inis[i].item=2;
        }
        sala->inis[i].item=1;

        //sala->inis[i].item=(rand() % 2);
        //sala->inis[i].cod=(rand() % 2);

        sala->inis[i].timer=0;

        desenha_inimigo(&sala->inis[i]);
    }
}
