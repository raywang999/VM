#ifndef COMBONM_RUNNER_H
#define COMBONM_RUNNER_H


#include "lib/command/runner/command_runner.h"
#include "lib/window/window.h"
#include "lib/command/runner/movement_runner.h"
#include "lib/command/runner/normal_runner.h"
#include "lib/statusbar/root_status.h"

// takes a basic Normal mode Command and runs it
class ComboNMRunner: public CommandRunner<ComboNM>{
  Window*& activeWindow;
  Clipboard& clipboard;
  RootStatus& rootStatus;

  // helper runners
  MovementRunner movementRunner{activeWindow};
  NormalRunner normalRunner{activeWindow, clipboard, rootStatus};

 public:
  // the command must be one of a,i,o,s,A,I,O,R,S
  void run(const ComboNM* cmd); 
  ComboNMRunner(
    Window*& activeWindow, 
    Clipboard& clipboard,
    RootStatus& rootStatus
  ): 
    activeWindow{activeWindow}, 
    clipboard{clipboard}, 
    rootStatus{rootStatus}
  {}
};

#endif

