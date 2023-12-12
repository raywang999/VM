#ifndef INIT_REPLACE_MODE_H
#define INIT_REPLACE_MODE_H

#include "../init_windows.h"

#include "lib/mode/mode_manager.h"

#include "lib/command/parser/replace_parser.h"
#include "lib/command/runner/replace_runner.h"
#include "lib/command/runner/replace_reflector.h"

// set up parsers and runners for replace 
struct ReplaceModeClosure{
  WindowsClosure& windowsClosure;
  Window*& activeWindow{windowsClosure.activeWindow};
  
  ModeManager& rootModeManager;
  
  // setup replace Mode parsers and runners
  ReplaceParser replaceParser;
  ReplaceRunner replaceRunner{activeWindow, rootModeManager};
  ReplaceReflector replaceReflector{activeWindow};
  Mode replaceMode{&replaceParser, &replaceReflector};
  
  ReplaceModeClosure( ModeManager& rootModeManager, WindowsClosure& windows): 
    windowsClosure{windows}, rootModeManager{rootModeManager} 
  {
    replaceParser.attach(&replaceRunner);
    rootModeManager.attach(ModeType::Replace, &replaceMode);
  }

};

#endif
