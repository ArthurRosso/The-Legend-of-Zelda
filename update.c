#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>    // poll(), struct pollfd e POLLIN
#include <time.h>

#include "Structs/sala.h"
#include "Structs/jogador.h"
#include "Structs/inimigo.h"

// Atualiza uma instancia de mundo, se passando deltaTime segundos
int update (SALA *sala, float deltaTime)
{
    int i, c;
    char mesg[]="Pontuacao: %d    Vida: %d    Nivel: %d";

    mvprintw(2,(COLS-strlen(mesg))/2,"Pontuacao: %d   Vida: %d   Nivel: %d",sala->link.pont, sala->link.vida, sala->link.nivel);

    c = getch();
    if (c == ESC){
        return c;
    }

    for (i=0; i < sala->numInis; i++)
    {
        updateInimigo(sala, &sala->inis[i], deltaTime);

    }

    move_jogador(sala, c);
}
