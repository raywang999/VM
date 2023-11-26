// wrap ncurses into a namespace 
// - provide type-checking for some macros
// - provide aliases 
#ifndef CPP_NCURSES_H
#define CPP_NCURSES_H

#include <ncurses.h>

namespace ncurses{
using Window_t = WINDOW;
inline void getwindowhw(Window_t *win, int& height, int& width){
  getmaxyx(win, height, width);
}

// wrapper for ncurses attributes 
using Attribute = int;
namespace attribute{
  constexpr int Normal = A_NORMAL;
  constexpr int Standout = A_NORMAL;
  constexpr int ColorPair(int n) { return COLOR_PAIR(n); }
}

// wrapper for ncurses colors
// define colorsets in `ncolors.h`
namespace colorset{
  using color = short;
  using color_pair = short;
}

inline int print(int row, int col, const char* str) {
  return mvprintw(row, col, "%s", str);
}

inline int print(int row, int col, char ch) {
  return mvaddch(row, col, ch);
}

// set attributes to `num` chars starting from row, col 
inline int setAttributes(int row, int col, int num, Attribute attr, colorset::color_pair color_pair){ 
  return mvchgat(row, col, num, attr, color_pair, NULL);
}

}

#endif
