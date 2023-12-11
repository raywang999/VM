#ifndef INIT_NORMAL_MODE_H
#define INIT_NORMAL_MODE_H

#include "../parse_args.h"
#include "../init_windows.h"

#include "lib/mode/mode_manager.h"
#include "lib/mode/normal_mode.h"

#include "lib/command/runner/normal_runner.h"
#include "lib/command/runner/movement_runner.h"
#include "lib/command/runner/ctrl_runner.h"
#include "lib/command/runner/macro_runner.h"
#include "lib/command/runner/parser_group.h"
#include "lib/command/runner/jk_recorder.h"
#include "lib/command/runner/semi_colon_repeater.h"
#include "lib/cursor/cursor_recorder.h"

#include "lib/command/parser/normal_parser.h"
#include "lib/command/parser/movement_parser.h"
#include "lib/command/parser/ctrl_parser.h"
#include "lib/command/parser/macro_parser.h"

#include "lib/registers/clipboard.h"

// set up parsers and runners for basic normal mode commands
struct NormalModeClosure{
  WindowsClosure& windowsClosure;
  Window*& activeWindow{windowsClosure.activeWindow};
  ModeManager& rootModeManager;
  Clipboard& clipboard;
  
  // setup parsers
  NormalParser normalParser;
  MovementParser movementParser;
  CtrlParser ctrlParser;
  MacroParser macroParser;
  // setup runners
  MovementRunner movementRunner{activeWindow};
  JKRecorder jkRecorder{movementRunner};
  CtrlRunner ctrlRunner{activeWindow, movementRunner};
  NormalRunner normalRunner{ activeWindow, clipboard, windowsClosure.rootStatus };
  SemiColonRepeater semiColonRepeater{movementRunner};

  
  // setup the core mode
  ParserGroup normalGroup;
  NormalMode normalMode{normalGroup};

  // creates a Mode manager, Modes, and links between parsers and runners
  NormalModeClosure(
    ModeManager& rootModeManager, 
    WindowsClosure& windows, 
    Clipboard& clipboard, 
    CursorRecorder& cursorRecorder
  ): windowsClosure{windows}, rootModeManager{rootModeManager}, clipboard{clipboard}{
    movementParser.attach(&movementRunner);
    normalParser.attach(&cursorRecorder);
    normalParser.attach(&normalRunner);
    ctrlParser.attach(&ctrlRunner);
    // ensure jk remembers its largest column
    movementParser.attach(static_cast<CommandRunner<Movement>*>(&jkRecorder));
    movementParser.attach(&semiColonRepeater);
    normalParser.attach(&jkRecorder);
    rootModeManager.attach(ModeType::Normal, &normalMode);
    
    normalGroup.add(&macroParser);
    normalGroup.add(&normalParser);
    normalGroup.add(&ctrlParser);
    normalGroup.add(&movementParser);

    normalMode.attach_consumer(&normalGroup);
  }

};

#endif
