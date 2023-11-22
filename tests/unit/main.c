
#include <stdio.h>
#include <ncurses.h>

int main(){
  initscr();
	clear();
	noecho();
  keypad(stdscr, TRUE);
  while (1){
    int c = getch();
    printw("%3d, %c", c,c);
    refresh();
  }
  endwin();
}
