// wrap ncurses into a namespace 
// - provide type-checking for some macros
// - provide aliases 
#ifndef CPP_NCURSES_H
#define CPP_NCURSES_H

namespace ncurses{
  #include <ncurses.h>
  using Window_t = WINDOW;
  void getmaxyx(Window_t *win, int& y, int& x){
    getmaxyx(win, y, x);
  }
}

#endif
