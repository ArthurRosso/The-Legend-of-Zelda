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

// TODO: Colocar no inimigo.h
#define timeIni 0.2
// TODO: Colocar no jogador.h
#define timeLink 0.1

// Atualiza uma instancia de mundo, se passando deltaTime segundos
int update (SALA *sala)
{
    int i, c=5;
    char mesg[]="Pontuacao: %d    Vida: %d    Nivel: %d";

    while (c != ESC){
        mvprintw(2,(COLS-strlen(mesg))/2,"Pontuacao: %d   Vida: %d   Nivel: %d",sala->link.pont, sala->link.vida, sala->link.nivel);

        for (i=0; i < sala->numInis; i++)
        {
            mvprintw(3,(COLS-strlen(mesg))/2,"Debugger: %f sala->inis[i].timer entrou no for", sala->inis[i].timer);
            updateInimigo(sala, &sala->inis[i], timeIni);
        }
    
        // cada lance do timer o jogador pode se mover
        if (sala->link.timer >= 1)
        {
            mvprintw(5,(COLS-strlen(mesg))/2,"Debugger: %f sala->link.timer entrou no if", sala->link.timer);
            sala->link.timer = 0;
            c = getch();
            if (c == ESC){
                return c;
            }
            move_jogador(sala, c);
        } else {
            // Aumeta o timer
            sala->link.timer += timeLink;
            mvprintw(4,(COLS-strlen(mesg))/2,"Debugger: %f sala->link.timer", sala->link.timer);
        }
    }

    return 0;
}
