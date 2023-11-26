// wrap ncurses into a namespace 
// - provide type-checking for some macros
// - provide aliases 
#ifndef NCOLORS_H
#define NCOLORS_H

#include "ncursespp.h"

// colorsets for ncurses
namespace ncurses{
namespace colorset{
  constexpr color ColorBackground = 8;
  constexpr color ColorError = 9;
  constexpr color ColorComments = 10;
  constexpr color ColorKeywords = 11;
  constexpr color ColorFunctions = 12;
  constexpr color ColorVariables = 13;
  constexpr color ColorLineStart = 14;
  constexpr color ColorText = 15;
  constexpr color_pair PairDefault = 1;
  constexpr color_pair PairLineStart = 2;
  // functions that will initialize ncurses with the given colors
  inline void copy_color(color From, color To){
    short r,g,b;
    color_content(From, &r, &g, &b);
    init_color(To, r,g,b);
  }
  inline void standard(){
    copy_color(COLOR_BLACK, ColorBackground);
    copy_color(COLOR_WHITE, ColorText);
    copy_color(COLOR_RED, ColorError);
    init_pair(PairDefault, ColorText, ColorBackground);
    init_pair(PairLineStart, ColorLineStart, ColorBackground);
  }
}
}

#endif
