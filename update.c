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
int update (SALA *sala, float deltaTimeIni, float deltaTimeLink)
{
    int i, c=5;
    char mesg[]="Pontuacao: %d    Vida: %d    Nivel: %d";

    mvprintw(2,(COLS-strlen(mesg))/2,"Pontuacao: %d   Vida: %d   Nivel: %d",sala->link.pont, sala->link.vida, sala->link.nivel);

    // Aumeta o timer
    sala->link.timer += deltaTimeLink;

    // cada lance do timer o inimigo pode se mover
    if (sala->link.timer >= 1)
    {
        c = getch();
        if (c == ESC){
            return c;
        }
        move_jogador(sala, c);
    }

    for (i=0; i < sala->numInis; i++)
    {
        updateInimigo(sala, &sala->inis[i], deltaTimeIni);

    }
}
