#ifndef INIT_NORMAL_MODE_H
#define INIT_NORMAL_MODE_H

#include "../parse_args.h"
#include "../init_windows.h"
#include "../init_history.h"

#include "lib/mode/mode_manager.h"
#include "lib/mode/normal_mode.h"

#include "lib/command/runner/normal_runner.h"
#include "lib/command/runner/movement_runner.h"
#include "lib/command/runner/ctrl_runner.h"
#include "lib/command/runner/macro_runner.h"
#include "lib/command/runner/parser_group.h"
#include "lib/command/runner/jk_recorder.h"
#include "lib/command/runner/semi_colon_repeater.h"
#include "lib/command/runner/comboNM_runner.h"
#include "lib/matcher/matcher_runner.h"

#include "lib/command/parser/comboNM_parser.h"
#include "lib/command/parser/normal_parser.h"
#include "lib/command/parser/movement_parser.h"
#include "lib/command/parser/ctrl_parser.h"

#include "lib/registers/clipboard.h"

// set up parsers and runners for normal mode commands
struct NormalModeClosure{
  WindowsClosure& windowsClosure;
  Window*& activeWindow{windowsClosure.activeWindow};
  HistoryClosure& historyClosure;
  ModeManager& rootModeManager;
  Clipboard& clipboard;
  
  // setup parsers
  NormalParser normalParser;
  MovementParser movementParser;
  CtrlParser ctrlParser;
  ComboNMParser comboNMParser;

  // setup runners
  MovementRunner movementRunner{activeWindow};
  JKRecorder jkRecorder{movementRunner};
  CtrlRunner ctrlRunner{activeWindow, windowsClosure.rootStatus, historyClosure.historyManager};
  NormalRunner normalRunner{ activeWindow, clipboard, windowsClosure.rootStatus };
  SemiColonRepeater semiColonRepeater{movementRunner};
  ComboNMRunner comboNMRunner{activeWindow, clipboard, windowsClosure.rootStatus};
  MatcherRunner matcherRunner{activeWindow, historyClosure.historyManager};

  
  // setup the core mode
  ParserGroup normalGroup;
  NormalMode normalMode{normalGroup};

  // creates a Mode manager, Modes, and links between parsers and runners
  NormalModeClosure(
    ModeManager& rootModeManager, 
    WindowsClosure& windows, 
    HistoryClosure& history,
    Clipboard& clipboard
  ): windowsClosure{windows}, historyClosure{history}, 
    rootModeManager{rootModeManager}, clipboard{clipboard}
  {
    movementParser.attach(&movementRunner);
    movementParser.attach(&matcherRunner);
    normalParser.attach(&historyClosure.cursorRecorder);
    normalParser.attach(&normalRunner);
    ctrlParser.attach(&ctrlRunner);
    comboNMParser.attach(&comboNMRunner);
    // ensure jk remembers its largest column
    movementParser.attach(static_cast<CommandRunner<Movement>*>(&jkRecorder));
    movementParser.attach(&semiColonRepeater);
    normalParser.attach(&jkRecorder);
    rootModeManager.attach(ModeType::Normal, &normalMode);
    
    normalGroup.add(&normalParser);
    normalGroup.add(&comboNMParser);
    normalGroup.add(&ctrlParser);
    normalGroup.add(&movementParser);

    normalMode.attach_consumer(&normalGroup);
  }

};

#endif
