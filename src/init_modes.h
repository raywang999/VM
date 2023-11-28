#ifndef INIT_MODES_H
#define INIT_MODES_H

#include <string>

#include "parse_args.h"
#include "init_windows.h"

#include "lib/mode/mode_manager.h"
#include "lib/mode/insert_mode.h"
#include "lib/command/parser/normal_parser.h"
#include "lib/buffer/file_manager.h"
#include "lib/tab/tabmanager.h"
#include "lib/keystroke/keystroke_source.h"
#include "lib/tab/tab.h"
#include "lib/mode/insert_reflector.h"

struct ModesClosure{
  WindowsClosure& windowsClosure;

  ModeManager rootModeManager;
  
  InsertParser insertParser;
  InsertReflector insertReflector{windowsClosure.activeWindow};
  InsertRunner insertRunner{windowsClosure.activeWindow, insertParser};

  // whether we have exited from the rootWindow
  bool exitedFromRoot = false;

  // creates a Mode manager, Modes, and links between parsers and runners
  ModesClosure(WindowsClosure& windows, KeystrokeSource& keyboard): 
    windowsClosure{windows}
  {
    // setup Insert Mode
    InsertMode insertMode(insertParser);
    insertMode.attach_consumer(&insertReflector);
    insertParser.attach(&insertRunner);
    rootModeManager.attach(ModeType::Insert, &insertMode);
    
    // setup Normal Mode
    NormalParser normalParser;
    Mode normalMode({&normalParser});
    rootModeManager.attach(ModeType::Normal, &normalMode);

    keyboard.attach(&rootModeManager);
  }
};

#endif
