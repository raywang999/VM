#ifndef SETMODE_RUNNER_H
#define SETMODE_RUNNER_H


#include "lib/command/runner/command_runner.h"
#include "lib/window/window.h"
#include "lib/mode/mode_manager.h"
#include "lib/command/parser/insert_parser.h"
#include "lib/command/runner/movement_runner.h"
#include "lib/command/parser/ex_parser.h"
#include "lib/statusbar/root_status.h"

// takes a basic Normal mode Command and runs it
class SetModeRunner: public CommandRunner<SetMode>{
  Window*& activeWindow;
  ModeManager& modeManager;
  InsertParser& insertParser;
  RootStatus& rootStatus;
  // helps with e.g. S, I
  MovementRunner movementRunner{activeWindow};

 public:
  // the command must be one of a,i,o,s,A,I,O,R,S
  void run(const SetMode* cmd); 
  SetModeRunner(
    Window*& activeWindow, 
    ModeManager& modeManager, 
    InsertParser& insertParser,
    RootStatus& rootStatus
  ): 
    activeWindow{activeWindow}, 
    modeManager{modeManager}, 
    insertParser{insertParser}, 
    rootStatus{rootStatus}
  {}
};

#endif

