#include "lib/keystroke/uwse_keyboard.h"
#include "include/ncursespp.h"
#include "include/ncolors.h"

int main(int argc, const char* argv[]){
  // initialize ncurses
  initscr();
  cbreak();
  start_color();
  keypad(stdscr, true);
  ncurses::colorset::standard();

  endwin();
}
