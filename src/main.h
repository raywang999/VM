#ifndef MAIN_H
#define MAIN_H

#include <memory>

#include "parse_args.h"
#include "init_ncurses.h"
#include "init_tabs.h"
#include "init_modes.h"
#include "init_windows.h"

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

  FileManager fileManager;
  StyleManager styleManager;

  // CS Student Environment Keyboard
  UWSEKeyboard keyboard;

  // initialize Tabs, root TabManager, activeTab with terminal supplied args
  TabsClosure tabsClosure{terminalArgs, fileManager};

  // initialize root `Window`
  WindowsClosure windowsClosure{tabsClosure, styleManager};
  
  // initialize Modes
  ModesClosure modesClosure{windowsClosure, keyboard};
  
  
  Main(int argc, const char *argv[]): 
    terminalArgs(argc, argv) {}
  
  // run the main loop
  int main();
};

#endif