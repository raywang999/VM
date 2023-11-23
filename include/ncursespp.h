// wrap ncurses into a namespace 
// - provide type-checking for some macros
// - provide aliases 
#ifndef CPP_NCURSES_H
#define CPP_NCURSES_H

#include <ncurses.h>
namespace ncurses{
  using Window_t = WINDOW;
  void getwindowhw(Window_t *win, int& height, int& width){
    getmaxyx(win, height, width);
  }
}

#endif
