#ifndef INIT_SEARCH_MODE_H
#define INIT_SEARCH_MODE_H

#include "../parse_args.h"
#include "../init_windows.h"
#include "../init_history.h"
#include "init_normal.h"
#include "lib/mode/mode_manager.h"

#include "lib/command/runner/search_runner.h"
#include "lib/command/parser/search_parser.h"

// set up parsers and runners for search mode 
struct SearchModeClosure{
  WindowsClosure& windowsClosure;
  Window*& activeWindow{windowsClosure.activeWindow};
  ModeManager& rootModeManager;
  
  // setup parsers
  SearchParser searchParser;

  // setup runners
  SearchRunner searchRunner{
    activeWindow, 
    windowsClosure.rootStatus, 
    rootModeManager
  };

  
  Mode searchMode;
  // creates a search Mode manager, Modes, and links between parsers and runners
  SearchModeClosure(
    ModeManager& rootModeManager, 
    WindowsClosure& windows
  ): windowsClosure{windows}, 
    rootModeManager{rootModeManager}
  {
    rootModeManager.attach(ModeType::Search, &searchMode);
    searchMode.attach_consumer(&searchParser);
    
    searchParser.attach(&searchRunner);
  }

};

#endif
