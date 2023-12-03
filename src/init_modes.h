#ifndef INIT_MODES_H
#define INIT_MODES_H

#include <string>

#include "parse_args.h"
#include "init_windows.h"

#include "lib/command/command_source.h"

#include "lib/mode/mode_manager.h"
#include "lib/mode/normal_mode.h"
#include "lib/mode/esc_normal.h"

#include "lib/command/runner/insert_reflector.h"
#include "lib/command/runner/insert_runner.h"
#include "lib/command/runner/normal_runner.h"
#include "lib/command/runner/movement_runner.h"
#include "lib/command/runner/ctrl_runner.h"
#include "lib/command/runner/macro_runner.h"
#include "lib/command/runner/parser_group.h"

#include "lib/command/parser/normal_parser.h"
#include "lib/command/parser/movement_parser.h"
#include "lib/command/parser/ctrl_parser.h"
#include "lib/command/parser/macro_parser.h"
#include "lib/command/parser/ex_parser.h"

#include "lib/command/history_manager.h"

#include "lib/buffer/file_manager.h"
#include "lib/tab/tabmanager.h"
#include "lib/keystroke/keystroke_source.h"

struct ModesClosure{
  WindowsClosure& windowsClosure;

  ModeManager rootModeManager;
  
  // esc keys will set the rootModeManager to normal mode
  EscNormal escNormal{rootModeManager};

  // setup CommandRecorder for history and macros
  CommandRecorder historyRecorder;
  CommandRecorder macroRecorder;

  // setup Insert Mode
  InsertParser insertParser;
  InsertRunner insertRunner{windowsClosure.activeWindow};
  InsertReflector insertReflector{windowsClosure.activeWindow};
  Mode insertMode{&insertParser, &insertReflector, &escNormal};


  // setup Normal Mode
  ParserGroup normalGroup;
  NormalParser normalParser;
  MovementParser movementParser;
  CtrlParser ctrlParser;
  MacroParser macroParser;
  NormalMode normalMode{normalGroup};
  MovementRunner movementRunner{windowsClosure.activeWindow};
  CtrlRunner ctrlRunner{windowsClosure.activeWindow, movementRunner};

  // general runner for all users
  SingleRunner singleRunner{normalRunner, insertRunner, movementRunner};
  SequenceRunner sequenceRunner{singleRunner};
  GeneralRunner generalRunner{singleRunner, sequenceRunner};
  // setup history manager
  HistoryManager manager{historyRecorder, generalRunner};

  NormalRunner normalRunner{windowsClosure.activeWindow, rootModeManager, insertParser, exParser};
  MacrosRegister macrosRegister;
  MacroRunner macroRunner{sequenceRunner, macrosRegister, macroRecorder};

  // setup Ex Mode 
  ExParser exParser;
  Mode exMode{&exParser, &escNormal};


  // whether we have exited from the rootWindow
  bool exitedFromRoot = false;

  // creates a Mode manager, Modes, and links between parsers and runners
  ModesClosure(WindowsClosure& windows, KeystrokeSource& keyboard): 
    windowsClosure{windows}
  {
    // setup Insert Mode
    insertParser.attach(&insertRunner);
    rootModeManager.attach(ModeType::Insert, &insertMode);
    
    // setup Normal Mode
    movementParser.attach(&movementRunner);
    normalParser.attach(&normalRunner);
    ctrlParser.attach(&ctrlRunner);
    macroParser.attach(&macroRunner);
    rootModeManager.attach(ModeType::Normal, &normalMode);

    // setup history 
    normalParser.attach(&historyRecorder);
    insertParser.attach(&historyRecorder);
    movementParser.attach(&historyRecorder);

    // setup Ex mode 
    rootModeManager.attach(ModeType::Ex, &exMode);

    // attach the root mode manager to the keyboard
    keyboard.attach(&rootModeManager);

    // attach ParserGroup last since they will reset the parsers
    normalMode.attach_consumer(&normalGroup);
    macroParser.attach(&normalGroup);
    movementParser.attach(&normalGroup);
    normalParser.attach(&normalGroup);
    ctrlParser.attach(&normalGroup);
    normalGroup.add(&macroParser);
    normalGroup.add(&normalParser);
    normalGroup.add(&ctrlParser);
    normalGroup.add(&movementParser);
  }

};

#endif
