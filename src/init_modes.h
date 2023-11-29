#ifndef INIT_MODES_H
#define INIT_MODES_H

#include <string>

#include "parse_args.h"
#include "init_windows.h"

#include "lib/mode/mode_manager.h"
#include "lib/mode/insert_mode.h"
#include "lib/mode/normal_mode.h"

#include "lib/command/runner/insert_reflector.h"
#include "lib/command/runner/insert_runner.h"
#include "lib/command/runner/normal_runner.h"
#include "lib/command/runner/movement_runner.h"
#include "lib/command/runner/ctrl_runner.h"
#include "lib/command/runner/macro_runner.h"

#include "lib/command/parser/normal_parser.h"
#include "lib/command/parser/movement_parser.h"
#include "lib/command/parser/ctrl_parser.h"
#include "lib/command/parser/macro_parser.h"

#include "lib/buffer/file_manager.h"
#include "lib/tab/tabmanager.h"
#include "lib/keystroke/keystroke_source.h"

struct ModesClosure{
  WindowsClosure& windowsClosure;

  ModeManager rootModeManager;
  
  // setup Insert Mode
  InsertParser insertParser;
  InsertReflector insertReflector{windowsClosure.activeWindow};
  InsertRunner insertRunner{windowsClosure.activeWindow, insertParser};
  InsertMode insertMode{insertParser};

  // setup Normal Mode
  NormalParser normalParser;
  MovementParser movementParser;
  CtrlParser ctrlParser;
  MacroParser macroParser;
  NormalMode normalMode{normalParser, movementParser};
  MovementRunner movementRunner{windowsClosure.activeWindow, normalMode};
  CtrlRunner ctrlRunner{windowsClosure.activeWindow, movementRunner};
  MacroRunner macroRunner{windowsClosure.activeWindow};
  NormalRunner normalRunner{windowsClosure.activeWindow, normalMode, insertParser};

  // whether we have exited from the rootWindow
  bool exitedFromRoot = false;

  // creates a Mode manager, Modes, and links between parsers and runners
  ModesClosure(WindowsClosure& windows, KeystrokeSource& keyboard): 
    windowsClosure{windows}
  {
    // setup Insert Mode
    insertMode.attach_consumer(&insertReflector);
    insertParser.attach(&insertRunner);
    rootModeManager.attach(ModeType::Insert, &insertMode);
    
    // setup Normal Mode
    movementParser.attach(&movementRunner);
    normalParser.attach(&normalRunner);
    ctrlParser.attach(&ctrlRunner);
    macroParser.attach(&macroRunner);
    rootModeManager.attach(ModeType::Normal, &normalMode);

    keyboard.attach(&rootModeManager);
  }
};

#endif
