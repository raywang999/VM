#ifndef INIT_MODES_H
#define INIT_MODES_H

#include "../init_history.h"
#include "init_normal.h"
#include "init_insert.h"
#include "init_replace.h"
#include "init_search.h"

#include "lib/command/command_source.h"

#include "lib/mode/mode_manager.h"

#include "lib/command/runner/macro_runner.h"
#include "lib/command/runner/ex_runner.h"
#include "lib/command/runner/dot_repeater.h"
#include "lib/command/runner/undo_runner.h"
#include "lib/command/runner/setmode_runner.h"
#include "lib/command/runner/message_reseter.h"
#include "lib/command/runner/at_runner.h"

#include "lib/command/parser/setmode_parser.h"
#include "lib/command/parser/macro_parser.h"

#include "lib/mode/esc_normal.h"

#include "lib/keystroke/keystroke_recorder.h"
#include "lib/keystroke/keystroke_source.h"

#include "lib/registers/clipboard.h"

struct ModesClosure{
  WindowsClosure& windowsClosure;
  Window*& activeWindow{windowsClosure.activeWindow};
  TabsClosure& tabsClosure;
  HistoryClosure& historyClosure;
  HistoryRecorder& historyRecorder = historyClosure.historyRecorder;
  HistoryManager& historyManager = historyClosure.historyManager;

  
  ModeManager rootModeManager;
  Clipboard rootClipboard;
  
  // setup CommandRecorder for history and macros
  KeystrokeRecorder macroRecorder;

  // basic normal mode
  NormalModeClosure normalModeClosure{
    rootModeManager, windowsClosure, historyClosure, rootClipboard
  };

  // esc keys will set the rootModeManager to normal mode
  EscNormal escNormal{rootModeManager};
  
  // insert mode
  InsertModeClosure insertModeClosure{rootModeManager, windowsClosure};
  
  // replace mode
  ReplaceModeClosure replaceModeClosure{rootModeManager, windowsClosure};

  SearchModeClosure searchModeClosure{rootModeManager, windowsClosure, normalModeClosure};

  // setup Macros
  MacroParser macroParser;
  MacrosRegister macrosRegister;
  MacroRunner macroRunner{
    macrosRegister, macroRecorder, rootModeManager, macroParser, 
    normalModeClosure.normalGroup, 
    historyClosure.macroRecorder, 
    historyClosure.historyRecorder
  };
  // setup Ex Mode 
  ExParser exParser;
  ExRunner exRunner{
    activeWindow, rootModeManager,
    windowsClosure.rootStatus, tabsClosure.fileManager, historyManager,
  };
  Mode exMode{&exParser, &escNormal};

  // add setMode runner and parsers
  SetModeRunner setModeRunner{activeWindow, rootModeManager, 
    insertModeClosure.insertParser, windowsClosure.rootStatus, 
    replaceModeClosure.replaceParser, normalModeClosure.comboNMRunner};
  SetModeParser setModeParser;
  
  // setup DotRepeater for '.' normal commands
  DotRepeater dotRepeater{
    insertModeClosure.insertRunner, 
    normalModeClosure.normalRunner, 
    macroRunner, setModeRunner, normalModeClosure.comboNMRunner, 
    replaceModeClosure.replaceRunner
  };

  // add undo runner
  UndoRunner undoRunner{
    activeWindow, rootModeManager, historyManager, windowsClosure.rootStatus};

  MessageResetter messageResetter{windowsClosure.rootStatus};
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
    // setup the keyboard
    keyboard.attach(&macroRecorder);
    keyboard.attach(&rootModeManager);

    // setup cursorRecorder to save cursor state before each command
    macroParser.attach(&historyClosure.cursorRecorder);
    replaceModeClosure.replaceParser.attach(
      static_cast<CommandRunner<Replace>*>(&historyClosure.cursorRecorder));
    insertModeClosure.insertParser.attach(
      static_cast<CommandRunner<Insert>*>(&historyClosure.cursorRecorder));
    exParser.attach(&historyClosure.cursorRecorder);
    normalModeClosure.normalParser.attach(&historyClosure.cursorRecorder);
    normalModeClosure.movementParser.attach(&historyClosure.cursorRecorder);

    // same for macro Cursor
    macroParser.attach(&historyClosure.macroCursor);
    replaceModeClosure.replaceParser.attach(
      static_cast<CommandRunner<Replace>*>(&historyClosure.macroCursor));
    insertModeClosure.insertParser.attach(
      static_cast<CommandRunner<Insert>*>(&historyClosure.macroCursor));
    exParser.attach(&historyClosure.macroCursor);
    normalModeClosure.normalParser.attach(&historyClosure.macroCursor);
    normalModeClosure.movementParser.attach(&historyClosure.macroCursor);

    // setup setMode 
    setModeParser.attach(&setModeRunner);
    normalModeClosure.normalGroup.add(&setModeParser);
    setModeParser.attach(&searchModeClosure.searchParser);

    // setup Ex mode 
    exParser.attach(&exRunner);
    rootModeManager.attach(ModeType::Ex, &exMode);
    
    // setup dot repeater 
    normalModeClosure.normalParser.attach(&dotRepeater);
    normalModeClosure.comboNMParser.attach(&dotRepeater);
    insertModeClosure.insertParser.attach(&dotRepeater);
    replaceModeClosure.replaceParser.attach(&dotRepeater);
    setModeParser.attach(&dotRepeater);
    macroParser.attach(&dotRepeater);

    // setup macros 
    normalModeClosure.normalGroup.add(&macroParser);
    macroParser.attach(&macroRunner);

    // setup history 
    macroParser.attach(&historyRecorder);
    insertModeClosure.insertParser.attach(&historyRecorder);
    exParser.attach(&historyRecorder);
    normalModeClosure.normalParser.attach(&historyRecorder);
    normalModeClosure.normalParser.attach(&undoRunner);
    normalModeClosure.ctrlParser.attach(&undoRunner);
    normalModeClosure.comboNMParser.attach(&historyRecorder);
    replaceModeClosure.replaceParser.attach(&historyRecorder);


    // attach esc normals 
    insertModeClosure.insertMode.attach_consumer(&escNormal);
    searchModeClosure.searchMode.attach_consumer(&escNormal);

    // attach message resetter to relevant parsers
    normalModeClosure.normalParser.attach(&messageResetter);
    setModeParser.attach(&messageResetter);
    macroParser.attach(&messageResetter);

    // attach parsers to notify their ParserGroup last 
    // since the ParserGroup will reset the parsers
    auto &normalGroup = normalModeClosure.normalGroup;
    macroParser.attach(&normalGroup);
    normalModeClosure.movementParser.attach(&normalGroup);
    normalModeClosure.normalParser.attach(&normalGroup);
    normalModeClosure.ctrlParser.attach(&normalGroup);
    setModeParser.attach(&normalGroup);
    normalModeClosure.comboNMParser.attach(&normalGroup);
  }

};

#endif
