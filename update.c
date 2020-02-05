#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <poll.h> // poll(), struct pollfd e POLLIN
#include <time.h>

#include "Structs/sala.h"
#include "Structs/jogador.h"
#include "Structs/inimigo.h"

int deseja_salvar();
void ganhou(void);

// Atualiza uma instancia de mundo, se passando deltaTime segundos
int update(SALA *sala)
{
    int i, c;
    char mesg[] = "Pontuacao: %d    Vida: %d    Nivel: %d";

    while (sala->link.vida != 0)
    {
        mvprintw(2, (COLS - strlen(mesg)) / 2, "Pontuacao: %d   Vida: %d   Nivel: %d", sala->link.pont, sala->link.vida, sala->link.nivel);

        for (i = 0; i < sala->numInis; i++)
        {
            updateInimigo(sala, &sala->inis[i], timeIni);
        }

        // cada lance do timer o jogador pode se mover
        if (sala->link.timer >= 1)
        {
            mvprintw(5, (COLS - strlen(mesg)) / 2, "Debugger: %f sala->link.timer entrou no if", sala->link.timer);
            //sala->link.timer = 0;
            c = getch();
            mvprintw(7, (COLS - strlen(mesg)) / 2, "Debugger: %d", c);
            refresh();
            if (c == ESC)
            {
                if (deseja_salvar() == 0)
                {
                    salva_sala(sala);
                }

                return 0;
            }
            move_jogador(sala, c);
        }
        else
        {
            // Aumeta o timer
            sala->link.timer += timeLink;
            mvprintw(4, (COLS - strlen(mesg)) / 2, "Debugger: %f sala->link.timer", sala->link.timer);
        }
    }
    ganhou();

    return 0;
}

int deseja_salvar()
{

    int i, c = 5, selecionado = 0, selecao = 0;
    char mesg1[] = "Deseja salvar o jogo?";
    char *op[] = {
        "Sim",
        "Nao",
    };

    clear();
    refresh();
    mvprintw(LINES / 2, (COLS - strlen(mesg1)) / 2, mesg1);

    while (1)
    {

        for (i = 0; i < 2; i++)
        {
            if (i == selecionado)
                attron(A_REVERSE);

            if (i)
            {
                mvprintw((LINES / 2) + 1, ((COLS - strlen(op[i])) / 2) + (i * 5), op[i]);
            }
            else
            {
                mvprintw((LINES / 2) + 1, ((COLS - strlen(op[i])) / 2) - 5, op[i]);
            }

            if (i == selecionado)
                attroff(A_REVERSE);
        }

        selecao = getch();
        switch (selecao)
        {
        case KEY_LEFT:
            selecionado--;
            if (selecionado < 0)
                selecionado = 0;
            break;
        case KEY_RIGHT:
            selecionado++;
            if (selecionado > 1)
                selecionado = 1;
            break;
        default:
            break;
        }

        if (selecao == 10)
            break;
    }

    refresh();
    clear();

    return selecionado;
}

void ganhou(){
    char mesg1[] = "Parabens!!!";
    char mesg2[] = "Voce terminou o jogo";
    char mesg5[] = "Aperte qualquer tecla para voltar ao menu...";

    clear();
    //refresh();
    mvprintw(LINES / 2, (COLS - strlen(mesg1)) / 2, mesg1);
    mvprintw(LINES / 2 + 1, (COLS - strlen(mesg2)) / 2, mesg2);
    refresh();
    sleep(5);
    mvprintw(LINES / 2 + 6, (COLS - strlen(mesg5)) / 2, mesg5);
    getch();
    clear();
}