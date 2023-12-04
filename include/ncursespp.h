// wrap ncurses into a namespace 
// - provide type-checking for some macros
// - provide aliases 
#ifndef CPP_NCURSES_H
#define CPP_NCURSES_H

#include <string>
#include <ncurses.h>

namespace ncurses{
using Window_t = WINDOW;
inline void getwindowhw(Window_t *win, int& height, int& width){
  getmaxyx(win, height, width);
}
inline void getwindowhw(int& height, int& width){getwindowhw(stdscr, height, width);}

// wrapper for ncurses attributes 
using Attribute = int;
namespace attribute{
  constexpr int Normal = A_NORMAL;
  constexpr int Void = 0; // don't change attributes
  constexpr int Standout = A_NORMAL;
  constexpr int ColorPair(int n) { return COLOR_PAIR(n); }
}

// wrapper for ncurses colors
// define colorsets in `ncolors.h`
using Color = short;
using Color_pair = short;

inline int print(int row, int col, const std::string& str) {
  return mvprintw(row, col, "%s", str.c_str());
}

inline int print(int row, int col, char ch) {
  return mvaddch(row, col, ch);
}

// set attributes to `num` chars starting from row, col 
inline int setAttributes(int row, int col, int num, Attribute attr, Color_pair color_pair){ 
  return mvchgat(row, col, num, attr, color_pair, NULL);
}

// set attributes of attr on, starting from now until you turn it off
inline int onAttributes(Attribute attr){
  return attron(attr);
}
// set attributes to attr, starting from now 
inline int setAttributes(Attribute attr){
  return attrset(attr);
}
// set attributes off
inline int offAttributes(Attribute attr){
  return attroff(attr);
}

inline int moveCursor(int row, int col){
  return move(row,col);
}

// clears a line on row, setting all beg <= i < end to ' '
inline void clearLine(int row, int beg, int end){
  std::string rest(end - beg, ' ');
  ncurses::print(row,beg,rest);
}

}

#endif
