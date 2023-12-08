#ifndef INIT_MODES_H
#define INIT_MODES_H

#include "../init_history.h"
#include "init_normal.h"
#include "init_insert.h"

#include "lib/command/command_source.h"

#include "lib/mode/mode_manager.h"

#include "lib/command/runner/macro_runner.h"
#include "lib/command/runner/ex_runner.h"
#include "lib/command/runner/dot_repeater.h"
#include "lib/command/runner/undo_runner.h"
#include "lib/command/runner/setmode_runner.h"

#include "lib/command/parser/setmode_parser.h"
#include "lib/command/parser/macro_parser.h"

#include "lib/mode/esc_normal.h"

#include "lib/keystroke/keystroke_recorder.h"
#include "lib/keystroke/keystroke_source.h"

struct ModesClosure{
  WindowsClosure& windowsClosure;
  Window*& activeWindow{windowsClosure.activeWindow};
  TabsClosure& tabsClosure;
  HistoryClosure& historyClosure;
  HistoryRecorder& historyRecorder = historyClosure.historyRecorder;
  HistoryManager& historyManager = historyClosure.historyManager;

  ModeManager rootModeManager;
  
  // setup CommandRecorder for history and macros
  KeystrokeRecorder macroRecorder;

  // basic normal mode
  NormalModeClosure normalModeClosure{rootModeManager, windowsClosure};

  // esc keys will set the rootModeManager to normal mode
  EscNormal escNormal{rootModeManager, normalModeClosure.normalGroup};
  
  // basic insert mode
  InsertModeClosure insertModeClosure{rootModeManager, windowsClosure};

  // setup Macros
  MacroParser macroParser;
  MacrosRegister macrosRegister;
  MacroRunner macroRunner{macrosRegister, macroRecorder, rootModeManager};
  
  // setup Ex Mode 
  ExParser exParser;
  ExRunner exRunner{
    activeWindow, rootModeManager,
    windowsClosure.rootStatus, tabsClosure.fileManager, historyManager,
  };
  Mode exMode{&exParser, &escNormal};

  // add setMode runner and parsers
  SetModeRunner setModeRunner{activeWindow, rootModeManager, 
    insertModeClosure.insertParser, exParser};
  SetModeParser setModeParser;
  
  // setup DotRepeater for '.' normal commands
  DotRepeater dotRepeater{
    insertModeClosure.insertRunner, 
    normalModeClosure.normalRunner, 
    macroRunner, setModeRunner
  };

  // add undo runner
  UndoRunner undoRunner{
    activeWindow, rootModeManager, historyManager, windowsClosure.rootStatus};

  // creates a Mode manager, Modes, and links between parsers and runners
  ModesClosure(
    WindowsClosure& windows, 
    KeystrokeSource& keyboard, 
    TabsClosure& tabsClosure, 
    HistoryClosure& historyClosure
  ): 
    windowsClosure{windows}, 
    tabsClosure{tabsClosure}, 
    historyClosure{historyClosure}
  {
    // setup cursorRecorder to save cursor state before each command
    macroParser.attach(&historyClosure.cursorRecorder);
    insertModeClosure.insertParser.attach(
      static_cast<CommandRunner<Insert>*>(&historyClosure.cursorRecorder));
    exParser.attach(&historyClosure.cursorRecorder);
    normalModeClosure.normalParser.attach(&historyClosure.cursorRecorder);
    normalModeClosure.movementParser.attach(&historyClosure.cursorRecorder);

    // setup setMode 
    setModeParser.attach(&setModeRunner);
    normalModeClosure.normalGroup.add(&setModeParser);

    // setup Ex mode 
    exParser.attach(&exRunner);
    rootModeManager.attach(ModeType::Ex, &exMode);
    
    // setup history 
    macroParser.attach(&historyRecorder);
    insertModeClosure.insertParser.attach(&historyRecorder);
    exParser.attach(&historyRecorder);
    normalModeClosure.normalParser.attach(&historyRecorder);
    normalModeClosure.normalParser.attach(&undoRunner);
    normalModeClosure.ctrlParser.attach(&undoRunner);

    // setup dot repeater 
    normalModeClosure.normalParser.attach(&dotRepeater);
    insertModeClosure.insertParser.attach(&dotRepeater);
    setModeParser.attach(&dotRepeater);
    macroParser.attach(&dotRepeater);


    // attach the root mode manager to the keyboard
    keyboard.attach(&rootModeManager);

    // attach esc normals 
    insertModeClosure.insertMode.attach_consumer(&escNormal);
    exMode.attach_consumer(&escNormal);

    // attach parsers to notify their ParserGroup last 
    // since the ParserGroup will reset the parsers
    auto &normalGroup = normalModeClosure.normalGroup;
    macroParser.attach(&normalGroup);
    normalModeClosure.movementParser.attach(&normalGroup);
    normalModeClosure.normalParser.attach(&normalGroup);
    normalModeClosure.ctrlParser.attach(&normalGroup);
  }

};

#endif