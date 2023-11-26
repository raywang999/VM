// wrap ncurses into a namespace 
// - provide type-checking for some macros
// - provide aliases 
#ifndef NCOLORS_H
#define NCOLORS_H

#include <unordered_map>
#include "ncursespp.h"

// colorsets for ncurses
namespace ncurses{
namespace colorset{
  constexpr Color ColorBackground = 8;
  constexpr Color ColorError = 9;
  constexpr Color ColorComments = 10;
  constexpr Color ColorKeywords = 11;
  constexpr Color ColorFunctions = 12;
  constexpr Color ColorVariables = 13;
  constexpr Color ColorLineStart = 14;
  constexpr Color ColorText = 15;
  constexpr Color_pair PairDefault = 1;
  constexpr Color_pair PairLineStart = 2;
  constexpr Color_pair PairStatusBar = 3;
  constexpr Color_pair PairStatusError = 4;
  // functions that will initialize ncurses with the given Colors
  inline void copy_color(Color From, Color To){
    short r,g,b;
    color_content(From, &r, &g, &b);
    init_color(To, r,g,b);
  }
  inline void standard(){
    copy_color(COLOR_BLACK, ColorBackground);
    copy_color(COLOR_WHITE, ColorText);
    copy_color(COLOR_RED, ColorError);
    copy_color(COLOR_BLUE, ColorLineStart);
    init_pair(PairDefault, ColorText, ColorBackground);
    init_pair(PairLineStart, ColorLineStart, ColorBackground);
    init_pair(PairStatusBar, ColorBackground, ColorText);
    init_pair(PairStatusError, ColorText, ColorError);
  }
  using ColorsetFn = void (*)();
  static std::unordered_map<std::string, ColorsetFn> colorsetmaps{
    {"standard", standard}
  };
}
}

#endif
