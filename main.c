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

int update (SALA *sala);
int menu ();

int main()
{
    initscr();
    setvbuf(stdout, NULL, _IOLBF, 0);
    keypad(stdscr, TRUE);
    cbreak();
    noecho();
    curs_set(0);
    //start_color();

    //init_pair(GRASS_PAIR, COLOR_BLACK, COLOR_GREEN);
    //init_pair(WATER_PAIR, COLOR_CYAN, COLOR_BLUE);
    //init_pair(MOUNTAIN_PAIR, COLOR_BLACK, COLOR_WHITE);
    //init_pair(PLAYER_PAIR, COLOR_BLACK, COLOR_GREEN);

    int op=0, sair=0;
    char mesg1[]="WRITTEN AND";
    char mesg2[]="DIRECTED BY";
    char mesg3[]="QUENTIM";
    char mesg4[]="TARANTINO";
    char mesg5[]="Aperte qualquer tecla para voltar ao menu...";
    SALA s;

    do{
        op = menu();
        
        switch (op)
        {
        case 0:
            /* Novo jogo */
            gera_sala(&s, 1);

            sair = update(&s);
            break;
            
        case 1:
            /* Carregar jogo */
            carrega_sala(&s);

            sair = update(&s);
            break;
            
        case 2:
            /* Recordes */
            break;
    
        case 3:
            /* Creditos */
            clear();
            //refresh();
            mvprintw(LINES/2,(COLS-strlen(mesg1))/2, mesg1);
            mvprintw(LINES/2+1,(COLS-strlen(mesg2))/2, mesg2);
            mvprintw(LINES/2+2,(COLS-strlen(mesg3))/2, mesg3);
            mvprintw(LINES/2+3,((COLS-strlen(mesg4))/2), mesg4);
            refresh();
            sleep(5);
            mvprintw(LINES/2+6,(COLS-strlen(mesg5))/2, mesg5);
            getch();
            clear();
            break;
        
        case 4:
            sair = 1;
            break;
        
        default:
            break;
        }
    }while (sair != 1);

    endwin();

    return 0;
}

int menu()
{

    int i, c;
    char name[]="THE LEGEND OF ZELDA";
    int szer, dlug;

    getmaxyx(stdscr, szer, dlug); 
    move(szer/2, (dlug-strlen(name))/2); 

    printw(name);

    refresh();

    WINDOW * menuwin=newwin(7, dlug-12, szer-9, 6); 
    box(menuwin, 0, 0);
    
    refresh();
    wrefresh(menuwin);
    keypad(menuwin, TRUE);

    char *op[] = {
        "Novo Jogo",
        "Carregar jogo",
        "Recordes",
        "Creditos",
        "Sair",
    };
    int selecao;
    int selecionado=0;

    while(1)
    {
        for(i = 0; i < 5; i++) {
            if(i == selecionado)
                wattron(menuwin, A_REVERSE);
            mvwprintw(menuwin, i+1, 1, op[i]);
            if (i == selecionado)
                wattroff(menuwin, A_REVERSE);
        }

        selecao = wgetch(menuwin);
        switch(selecao)
        {
        case KEY_UP:
            selecionado--;
            if(selecionado < 0) selecionado = 0;
            break;
        case KEY_DOWN:
            selecionado++;
            if(selecionado > 4) selecionado = 4;
            break;
        default:
            break;
        }

        if(selecao==10) break;
    }

    //printw("\nWybrano:%s", op[selecionado]);
    refresh();

    return selecionado;
}