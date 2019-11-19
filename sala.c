#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>    // poll(), struct pollfd e POLLIN
#include <time.h>

#include "jogador.h"
#include "inimigo.h"
#include "sala.h"

void gera_sala (SALA *sala){
  int i;
  time_t t;

  srand((unsigned) time(&t));

  for (i=0; i<=sala->dif; i++){
    sala->inis[i].vida=1;
    sala->inis[i].pos.y=rand() % LINES-3;
      if(LINES-8<=0){
        sala->inis[i].pos.y+=8;
      } else {
        sala->inis[i].pos.y-=8;
      }
    
    sala->inis[i].pos.x=rand() % COLS-3;
      if(COLS-8<=0){
        sala->inis[i].pos.x+=8;
      } else {
        sala->inis[i].pos.x-=8;
      }

    if (i==0){
        sala->inis[i].item=2;
    }
    sala->inis[i].item=(rand() % 2);
    sala->inis[i].cod=(rand() % 2);
  }
}
