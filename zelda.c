#include <curses.h>
#include <stdlib.h>

#define P_HEAD '#'
#define P_LARM '@'
#define P_TRO1 '#'
#define P_RARM '$'
#define P_LFOO '#'
#define P_TRO2 '#'
#define P_RFOO '#'


int main(void)
{
    int y, x;
    int ch;

    initscr();
    keypad(stdscr, TRUE);
    cbreak();
    noecho();
    curs_set(0);

    clear();

    y = LINES - 3;
    x = 0;

    do {
    clear();

	  mvaddch(y, x+1, P_HEAD);
    mvaddch(y+1, x, P_LARM);
    mvaddch(y+1, x+1, P_TRO1);
    mvaddch(y+1, x+2, P_RARM);
    mvaddch(y+2, x, P_LFOO);
    mvaddch(y+2, x+1, P_TRO2);
    mvaddch(y+2, x+2, P_RFOO);
	  move(y, x);
	  refresh();

	  ch = getch();

	  switch (ch) {
	     case KEY_UP:
	     case 'w':
	     case 'W':
	      if (y > 0) {
		       y = y - 1;
	      }
	     break;
	     case KEY_DOWN:
	case 's':
	case 'S':
	    if (y < LINES - 3) {
		y = y + 1;
	    }
	    break;
	case KEY_LEFT:
	case 'a':
	case 'A':
	    if (x > 0) {
		x = x - 1;
	    }
	    break;
	case KEY_RIGHT:
	case 'd':
	case 'D':
	    if (x < COLS - 3) {
		  x = x + 1;
	    }
	    break;
	}
    }
    while ((ch != 'q') && (ch != 'Q'));

    endwin();

    exit(0);
}
