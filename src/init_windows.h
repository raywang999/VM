#ifndef INIT_WINDOWS_H
#define INIT_WINDOWS_H

#include <string>

#include "include/ncursespp.h"
#include "init_tabs.h"
#include "lib/window/ncwindow.h"
#include "lib/statusbar/status_bar.h"
#include "lib/statusbar/root_status.h"
#include "lib/statusbar/root_status_render.h"

struct WindowsClosure{
  // data stored in rootStatusBar
  RootStatus rootStatus{};
  
  // renderer for status bar at the bottom of the screen
  RootStatusRender rootStatusRender{};
  
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
    rootStatusRender.translate(screenHeight-1,0);
    rootStatusRender.resize(1, screenWidth-20); 
    // right 20 chars are for the cursor
  }
};

#endif
