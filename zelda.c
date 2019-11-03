#include <curses.h>
#include <stdlib.h>

#define ESC 27
#define SPACE 32
#define EMPTY ' '

#define P_HEAD '#'
#define P_LARM '@'
#define P_TRO1 '#'
#define P_RARM '$'
#define P_LFOO '#'
#define P_TRO2 '#'
#define P_RFOO '#'
#define P_ATUD '|'
#define P_ATRL '-'

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

void desenha_jogador (int y, int x, int dir);
void ataque_magico (int y, int x, int dir);

int main(void)
{
  int p_y, p_x, p_dir=1;
  int ch;

  initscr();
  keypad(stdscr, TRUE);
  cbreak();
  noecho();
  curs_set(0);

  p_y = LINES - 3;
  p_x = 0;

  do {

    desenha_jogador(p_y, p_x, p_dir);

    ch = getch();

    switch (ch) {
      case KEY_UP:
      case 'w':
      case 'W':
      if (p_y > 0) {
        p_y = p_y - 1;
        p_dir=0;
      }
      break;
      case KEY_RIGHT:
      case 'd':
      case 'D':
      if (p_x < COLS - 3) {
        p_x = p_x + 1;
        p_dir=1;
      }
      break;
      case KEY_LEFT:
      case 'a':
      case 'A':
      if (p_x > 0) {
        p_x = p_x - 1;
        p_dir=2;
      }
      break;
      case KEY_DOWN:
      case 's':
      case 'S':
      if (p_y < LINES - 3) {
        p_y = p_y + 1;
        p_dir=3;
      }
      break;
      case SPACE:
        ataque_magico(p_y, p_x, p_dir);
      break;
    }
  }
  while ((ch != ESC));

  endwin();

  exit(0);
}

void desenha_jogador (int y, int x, int dir){
  switch (dir) {
    case 0:
      mvaddch(y+3, x, EMPTY);
      mvaddch(y+3, x+1, EMPTY);
      mvaddch(y+3, x+2, EMPTY);
      mvaddch(y+2, x, EMPTY);
      mvaddch(y, x+1, P_RARM);
      mvaddch(y+1, x, P_HEAD);
      mvaddch(y+1, x+1, P_TRO1);
      mvaddch(y+1, x+2, P_TRO2);
      mvaddch(y+2, x+2, P_LFOO);
      mvaddch(y+2, x+1, P_LARM);
      mvaddch(y, x+2, P_RFOO);
    break;
    case 1:
      mvaddch(y, x-1, EMPTY);
      mvaddch(y+1, x-1, EMPTY);
      mvaddch(y+2, x-1, EMPTY);
      mvaddch(y, x, EMPTY);
      mvaddch(y, x+1, P_HEAD);
      mvaddch(y+1, x, P_LARM);
      mvaddch(y+1, x+1, P_TRO1);
      mvaddch(y+1, x+2, P_RARM);
      mvaddch(y+2, x, P_LFOO);
      mvaddch(y+2, x+1, P_TRO2);
      mvaddch(y+2, x+2, P_RFOO);
    break;
    case 2:
      mvaddch(y, x+2, EMPTY);
      mvaddch(y, x+3, EMPTY);
      mvaddch(y+1, x+3, EMPTY);
      mvaddch(y+2, x+3, EMPTY);
      mvaddch(y, x+1, P_HEAD);
      mvaddch(y+1, x, P_RARM);
      mvaddch(y+1, x+1, P_TRO1);
      mvaddch(y+1, x+2, P_LARM);
      mvaddch(y+2, x, P_LFOO);
      mvaddch(y+2, x+1, P_TRO2);
      mvaddch(y+2, x+2, P_RFOO);
    break;
    case 3:
      mvaddch(y, x, EMPTY);
      mvaddch(y-1, x+1, EMPTY);
      mvaddch(y-1, x+2, EMPTY);
      mvaddch(y-1, x+3, EMPTY);
      mvaddch(y, x+1, P_LARM);
      mvaddch(y+1, x, P_HEAD);
      mvaddch(y+1, x+1, P_TRO1);
      mvaddch(y+1, x+2, P_TRO2);
      mvaddch(y+2, x+2, P_LFOO);
      mvaddch(y+2, x+1, P_RARM);
      mvaddch(y, x+2, P_RFOO);
    break;
  }

  move(y, x);
  refresh();
}


void ataque_magico (int y, int x, int dir){
  int i;
  switch (dir) {
    case 0:
    for (i=0; i<=y; i++){
      mvaddch(y-1-i, x+1, P_ATUD);
    }
    break;
    case 1:
      for (i=0; i<=COLS-x; i++){
        mvaddch(y+1, x+1+i, P_ATRL);
      }
    break;
    case 2:
      for (i=0; i<=x; i++){
        mvaddch(y+1, x+1-i, P_ATRL);
      }
    break;
    case 3:
      for (i=0; i<=LINES-y; i++){
        mvaddch(y-1+i, x+1, P_ATUD);
      }
    break;
  }
}
