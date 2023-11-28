#ifndef INIT_NCURSES
#define INIT_NCURSES

#include "parse_args.h"
#include "include/ncursespp.h"
#include "include/ncolors.h"

// Closure for objects and helper methods used to initialize Ncurses 
struct NcursesClosure{
 public: 
  // initialize ncurses
  NcursesClosure(TerminalArgs& terminalArgs) {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);
    int screenHeight, screenWidth;
    ncurses::getwindowhw(screenHeight, screenWidth);

    // show colors
    if (terminalArgs.hasOption(TerminalArgs::ShowColor{})){
      start_color();
    }
    // use a colorset
    if (terminalArgs.hasOption(TerminalArgs::SetColorset{})){
      auto it = terminalArgs.find(TerminalArgs::SetColorset{});
      auto colorset = std::get<TerminalArgs::SetColorset>(*(it));
      ncurses::colorset::colorsetmaps[colorset.colorset]();
    }
  }

  ~NcursesClosure(){endwin();}
};

#endif