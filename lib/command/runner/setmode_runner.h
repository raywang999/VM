#ifndef SETMODE_RUNNER_H
#define SETMODE_RUNNER_H


#include "lib/command/runner/command_runner.h"
#include "lib/window/window.h"
#include "lib/mode/mode_manager.h"
#include "lib/command/parser/insert_parser.h"
#include "lib/command/runner/comboNM_runner.h"
#include "lib/command/parser/replace_parser.h"
#include "lib/statusbar/root_status.h"

// takes a SetMode Command and runs it
class SetModeRunner: public CommandRunner<SetMode>{
  Window*& activeWindow;
  ModeManager& modeManager;
  InsertParser& insertParser;
  RootStatus& rootStatus;
  ReplaceParser& replaceParser;
  // helps with e.g. S, cM, s
  ComboNMRunner& comboNMRunner;

 public:
  // the command must be one of a,i,o,s,A,I,O,R,S
  void run(const SetMode* cmd); 
  SetModeRunner(
    Window*& activeWindow, 
    ModeManager& modeManager, 
    InsertParser& insertParser,
    RootStatus& rootStatus,
    ReplaceParser& replaceParser,
    ComboNMRunner& comboNMRunner
  ): 
    activeWindow{activeWindow}, 
    modeManager{modeManager}, 
    insertParser{insertParser}, 
    rootStatus{rootStatus},
    replaceParser{replaceParser}, 
    comboNMRunner{comboNMRunner}
  {}
};

#endif

