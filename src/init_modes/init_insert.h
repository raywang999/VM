#ifndef INIT_INSERT_MODE_H
#define INIT_INSERT_MODE_H

#include "../init_windows.h"

#include "lib/mode/mode_manager.h"

#include "lib/command/parser/insert_parser.h"
#include "lib/command/runner/insert_runner.h"
#include "lib/command/runner/insert_reflector.h"

// set up parsers and runners for insert mode 
struct InsertModeClosure{
  WindowsClosure& windowsClosure;
  Window*& activeWindow{windowsClosure.activeWindow};
  
  ModeManager& rootModeManager;
  
  // setup Insert Mode parsers and runners
  InsertParser insertParser;
  InsertRunner insertRunner{activeWindow, rootModeManager};
  InsertReflector insertReflector{activeWindow};
  Mode insertMode{&insertParser, &insertReflector};
  
  InsertModeClosure( ModeManager& rootModeManager, WindowsClosure& windows): 
    windowsClosure{windows}, rootModeManager{rootModeManager} 
  {
    insertParser.attach(&insertRunner);
    rootModeManager.attach(ModeType::Insert, &insertMode);
  }

};

#endif
