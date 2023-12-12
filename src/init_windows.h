#ifndef INIT_WINDOWS_H
#define INIT_WINDOWS_H

#include <string>

#include "include/ncursespp.h"
#include "init_tabs.h"
#include "lib/window/ncwindow.h"
#include "lib/statusbar/status_bar.h"
#include "lib/statusbar/root_status.h"

struct WindowsClosure{
  // root window that is displayed initially
  NCWindow rootWindow;
  // currently active unsplit Window
  Window* activeWindow = &rootWindow;

  // renderer for status bar at the bottom of the screen
  StatusBar rootStatusBar{};
  
  // data stored in rootStatusBar
  RootStatus rootStatus{};

  WindowsClosure(TabsClosure& tabs, StyleManager& styler): 
    rootWindow{tabs.rootTabManager,styler}
  { 
    int screenHeight, screenWidth;
    ncurses::getwindowhw(screenHeight, screenWidth);
    rootWindow.resize(screenHeight, screenWidth);
    rootWindow.translate(0,0);
    rootStatusBar.translate(screenHeight-1,0);
    rootStatusBar.resize(1, screenWidth);
  }
};

#endif
