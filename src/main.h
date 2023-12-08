#ifndef MAIN_H
#define MAIN_H

#include <memory>

#include "parse_args.h"
#include "init_ncurses.h"
#include "init_tabs.h"
#include "init_modes/init_modes.h"
#include "init_windows.h"
#include "init_cursor.h"
#include "init_statusbar.h"
#include "init_history.h"

#include "lib/keystroke/uwse_keyboard.h"
#include "lib/buffer/file_manager.h"
#include "lib/textbox/stylemanager.h"
#include "lib/window/ncwindow.h"

// helper functions and objects 
struct Main{
  // terminal arguments
  TerminalArgs terminalArgs;

  // ncurses initialization
  NcursesClosure ncursesClosure{terminalArgs};

  StyleManager styleManager;

  // CS Student Environment Keyboard
  UWSEKeyboard keyboard;

  // initialize Tabs, root TabManager, activeTab with terminal supplied args
  TabsClosure tabsClosure{terminalArgs};

  // initialize root `Window`
  WindowsClosure windowsClosure{tabsClosure, styleManager};

  // history 
  HistoryClosure historyClosure{tabsClosure, windowsClosure};
  
  // initialize Modes
  ModesClosure modesClosure{windowsClosure, keyboard, tabsClosure, historyClosure};

  // initialize the screen's cursor and statusbar
  CursorClosure cursorClosure{windowsClosure, modesClosure}; 
  StatusBarClosure statusBarClosure{windowsClosure, modesClosure}; 
  
  
  Main(int argc, const char *argv[]): 
    terminalArgs(argc, argv) {}
  
  // run the main loop
  int main();
};

#endif