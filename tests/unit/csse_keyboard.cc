#include <stdio.h>
#include <ncurses.h>

#include "csse_keyboard.h"

int main(){
  initscr();
	clear();
	noecho();
  keypad(stdscr, TRUE);
    int c = getch();
    assert(getch())
    refresh();
  endwin();
}

