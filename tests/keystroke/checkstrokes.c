#include <ncurses.h>

int main(){
  initscr();			/* Start curses mode 		  */
	//printw("Hello World !!!");	/* Print Hello World		  */
	//refresh();			/* Print it on to the real screen */
	//getch();			/* Wait for user input */
	endwin();			/* End curses mode		  */
  exit_curses(0);


	return 0;
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

