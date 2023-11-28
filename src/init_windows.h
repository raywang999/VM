#ifndef INIT_WINDOWS_H
#define INIT_WINDOWS_H

#include <string>

#include "include/ncursespp.h"
#include "init_tabs.h"
#include "lib/window/ncwindow.h"

struct WindowsClosure{
  // root window that is displayed initially
  NCWindow rootWindow;
  // currently active unsplit Window
  Window* activeWindow = &rootWindow;

  WindowsClosure(TabsClosure& tabs, StyleManager& styler): 
    rootWindow{tabs.rootTabManager,styler}
  { 
    int screenHeight, screenWidth;
    ncurses::getwindowhw(screenHeight, screenWidth);
    rootWindow.resize(screenHeight, screenWidth);
    rootWindow.translate(0,0);
  }
};

#endif
